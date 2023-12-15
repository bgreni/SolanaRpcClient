#pragma once
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <string_view>
#include "nlohmann/json.hpp"
#include <regex>
#include <iostream>

using json = nlohmann::json;

namespace net   = boost::asio;
namespace beast = boost::beast;
namespace http  = beast::http;
namespace ssl   = net::ssl;
using net::ip::tcp;

using Socket = beast::ssl_stream<beast::tcp_stream>;
using Buffer = beast::flat_buffer;


namespace Solana {

    using Request  = boost::beast::http::request<boost::beast::http::string_body>;

    class HttpClient {
    public:
        HttpClient(const std::string & endpoint)
            : ctx(boost::asio::ssl::context::tlsv13_client)
        {
            ctx.set_default_verify_paths();
            ctx.set_options(
                boost::asio::ssl::context::default_workarounds
                | boost::asio::ssl::context::no_sslv2
                | boost::asio::ssl::context::no_sslv3
            );
            // TODO: have a more robust way to set url
            std::regex re("(.+):\\/\\/(.+)\\/");
            std::cmatch m;
            std::regex_match(endpoint.c_str(), m, re);
            service = m[1];
            this->endpoint = m[2];
            targetBase = m[3];
        }
        ~HttpClient() {
            ioc.join();
            ioc.stop();
        }

        template<typename T>
        std::future<T> post(const json & body) {
            Request req{};
            req.method(beast::http::verb::post);
            req.target("/" + targetBase);
            req.set(beast::http::field::content_type, "application/json");
            req.body() = body.dump();
            auto res = performRequest<T>(req);
            return res;
        }

        template<typename T>
        std::future<T> performRequest(Request & request) {
            std::promise<T> promise;
            auto fut = promise.get_future();

            auto ex = make_strand(ioc);

            auto ep = tcp::resolver(ex).resolve(endpoint, service);

            std::shared_ptr<Socket> ssl_stream =
                std::make_shared<Socket>(ex, ctx);

            ssl_stream->set_verify_mode(ssl::verify_peer);

            // I don't fuckin know https://stackoverflow.com/questions/35175073/boost-ssl-verifies-expired-and-self-signed-certificates
            if(!SSL_set_tlsext_host_name(ssl_stream->native_handle(), endpoint.c_str()))
            {
                boost::system::error_code ec{static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category()};
                throw boost::system::system_error{ec};
            }

            ssl_stream->next_layer().connect(ep);
            ssl_stream->handshake(ssl::stream_base::handshake_type::client);
            auto coro = [this, r = request, p = std::move(promise), ssl_stream]
                (net::yield_context yield) mutable {
                try {
                    auto & s = *ssl_stream;

                    r.prepare_payload();
                    r.set(http::field::host, endpoint);
                    auto sent = http::async_write(s, r, yield);

                    Buffer buffer{};

                    http::response<http::string_body> res;
                    auto received = http::async_read(s, buffer, res, yield);
                    auto reply = T::parse(res.body());
                    p.set_value(std::move(reply));
                } catch (...) {
                    p.set_exception(std::current_exception());
                }
            };

            spawn(ssl_stream->get_executor(), std::move(coro));
            return fut;
        }
    private:

        boost::asio::thread_pool ioc = {};
        boost::asio::ssl::context ctx;
        std::string endpoint;
        std::string service;
        std::string targetBase;
    };
}



