#include <kademlia/session.hpp>
#include <kademlia/first_session.hpp>
#include <kademlia/error.hpp>
#include <future>
#include <iostream>
#include <iterator>
#include <vector>

// [...]

int main(){
	//-----------Initialization--------
	// The session need to know at least one member of the
	// distributed table to find neighbors.
	kademlia::endpoint const initial_peer_ipv4{ "127.0.0.1", 27980 };
	kademlia::endpoint const initial_peer_ipv6{ "::", 27980 };
	kademlia::endpoint const second_peer_ipv4{ "127.0.0.1", 27981 };
	kademlia::endpoint const second_peer_ipv6{ "::", 27981 };

	kademlia::first_session f{ initial_peer_ipv4, initial_peer_ipv6};
	std::cout << "setting up first peer complete." << std::endl;

	// If an error occurs, this will throw.
	// Following runtime errors will be reported
	// through an std::error_code.
	kademlia::session s{ initial_peer_ipv4, second_peer_ipv4, second_peer_ipv6};

	// Run the library main loop in a dedicated thread.
	auto main_loop_result = std::async( std::launch::async
			, &kademlia::session::run, &s );
	std::cout << "initialized" << std::endl;

	//-----------Saving a data into the table with "key1"---------
	// Testing data. 
	std::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);
	kademlia::session::data_type const data{ myvector.begin(), myvector.end() };

	// Create the handler.
	/* TODO: the callback functions are not executed due to a empty routing table
	   measure 1: enable debug flag
	   measure 2: add another node to the network. */
	auto on_save = []( std::error_code const& failure )
	{
		if ( failure )
			std::cerr << failure.message() << std::endl;
		std::cout << "saved key1" << std::endl;
	};

	// And perform the saving.
	const std::vector<unsigned char> key{'a'};
	s.async_save( key, data, on_save );
	std::cout << "saved key1" << std::endl;

	//-----------Searching for value associated with "key1"----------
	// This callback will be called once the load succeed or failed.
	auto on_load = []( std::error_code const& failure
			, kademlia::session::data_type const& data )
	{
		if ( failure )
			std::cerr << failure.message() << std::endl;
		else
			std::copy( data.begin(), data.end()
					, std::ostream_iterator< std::uint32_t >{ std::cout, " " } );
	};

	// Schedule an asynchronous load.
	s.async_load( key, on_load );
	auto res = main_loop_result.get();
	std::cout << "res" << res << std::endl;


	//-------------clean up ---------------
	// Once we've finished, abort the session::run()
	// blocking call.
	s.abort();

	auto failure = main_loop_result.get();
	if ( failure != kademlia::RUN_ABORTED )
		std::cerr << failure.message() << std::endl;
}
