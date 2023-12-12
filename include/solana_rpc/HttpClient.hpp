#pragma once
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <string_view>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace net   = boost::asio;
namespace beast = boost::beast;
namespace http  = beast::http;
namespace ssl   = net::ssl;
using net::ip::tcp;

namespace SolanaRpc {

    using Request  = http::request<http::string_body>;
    using Response = http::response<http::dynamic_body>;


    class HttpClient {
    public:
        HttpClient(const std::string & endpoint)
            : ctx(ssl::context::sslv3_client)
            , endpoint(endpoint)
            , ex(make_strand(ioc))
        {
            ctx.set_default_verify_paths();
        }

//        std::future<Response> post(const json & body);

        std::future<Response> post(const json & body) {
            Request req{};
            req.method(beast::http::verb::post);
            req.target("/");
            req.set(beast::http::field::content_type, "application/json");
            req.body() = body.dump();
            auto res = performRequest(req);
            return res;
        }

        std::future<Response> performRequest(const Request & request) {
            std::promise<Response> promise;
            auto fut = promise.get_future();
            auto ep = tcp::resolver(ex).resolve(endpoint, "https");
            beast::ssl_stream<beast::tcp_stream> ssl_stream(ex, ctx);
            ssl_stream.next_layer().connect(ep);
            ssl_stream.handshake(ssl::stream_base::handshake_type::client);
            auto coro = [&, this, r = request, p = std::move(promise)] //
                (net::yield_context yield) mutable {
                try {
                    auto &s = ssl_stream;
//            get_lowest_layer(s).expires_after(kTimeout);

                    r.prepare_payload();
                    r.set(http::field::host, endpoint);

                    http::async_write(s, r, yield);

                    beast::flat_buffer buffer{};

                    http::response<http::dynamic_body> res;
                    http::async_read(s, buffer, res, yield);
                    p.set_value(std::move(res));
                } catch (...) {
                    p.set_exception(std::current_exception());
                }
            };

            spawn(ssl_stream.get_executor(), std::move(coro));
            return fut;
        }

    private:

        net::thread_pool ioc = {};
        ssl::context ctx;
        net::any_io_executor ex;
        std::string endpoint;
    };
}



