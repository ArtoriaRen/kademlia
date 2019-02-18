/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   second_peer.cpp
 * Author: liuyangren
 *
 * Created on February 18, 2019, 5:55 PM
 */

#include <cstdlib>
#include <future>
#include <iostream>
#include <iterator>
#include <vector>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ip/v6_only.hpp>
#include <boost/system/system_error.hpp>
#include "../../include/kademlia/error.hpp"
#include "../../include/kademlia/endpoint.hpp"
#include "../../include/kademlia/session.hpp"
//using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
	//-----------Initialization--------
	// The session need to know at least one member of the
	// distributed table to find neighbors.
	kademlia::endpoint const initial_peer_ipv4{ "127.0.0.1", 27980 };
	kademlia::endpoint const second_peer_ipv4{ "127.0.0.1", 12345};
	kademlia::endpoint const second_peer_ipv6{ "::1", 27983 };

	// If an error occurs, this will throw.
	// Following runtime errors will be reported
	// through an std::error_code.
	kademlia::session s{ initial_peer_ipv4, second_peer_ipv4, second_peer_ipv6};
	// wait for peer discovery and routing table filling.


	// Run the library main loop in a dedicated thread.
	auto main_loop_result = std::async( std::launch::async
			, &kademlia::session::run, &s );
	std::cout << "initialized" << std::endl;

	sleep(5);

	//-----------Saving a data into the table with "key1"---------
	// Testing data. 
	std::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);
	kademlia::session::data_type const data{ myvector.begin(), myvector.end() };

	// Create the handler.
	auto on_save = []( std::error_code const& failure )
	{
		if ( failure ){
			std::cout << "failure happened on save" << std::endl;
			std::cerr << failure.message() << std::endl;
		}else{
			std::cout << "saved key1" << std::endl;
		}
	};

	// And perform the saving.
	const std::vector<unsigned char> key{'b'};
	s.async_save( key, data, on_save );
	//      auto res = main_loop_result.get();
	//      std::cout << "save res =" << res << std::endl;
	sleep(5);

	//-----------Searching for value associated with "key1"----------
	// This callback will be called once the load succeed or failed.
	auto on_load = []( std::error_code const& failure
			, kademlia::session::data_type const& data )
	{
		std::cout << "enter on_load" << std::endl;
		if ( failure ){
			std::cerr << failure.message() << std::endl;

			std::cout << "failure happen on load" << std::endl;
		}
		else {
			std::copy( data.begin(), data.end()
					, std::ostream_iterator< std::uint32_t >{ std::cout, " " } );
			std::cout << "finish printing data" << std::endl;
		}
	};

	// Schedule an asynchronous load.
	s.async_load( key, on_load );
	auto res1 = main_loop_result.get();
	std::cout << "load res" << res1 << std::endl;


	//-------------clean up ---------------
	// Once we've finished, abort the session::run()
	// blocking call.
	s.abort();

	auto failure = main_loop_result.get();
	if ( failure != kademlia::RUN_ABORTED )
		std::cerr << failure.message() << std::endl;

	return 0;
}

