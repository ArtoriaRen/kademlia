# Copyright (c) 2013, David Keller
# All rights reserved.
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the University of California, Berkeley nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY DAVID KELLER AND CONTRIBUTORS ``AS IS AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

set(kademlia_sources
    ${CMAKE_SOURCE_DIR}/include/kademlia/endpoint.hpp
    ${CMAKE_SOURCE_DIR}/include/kademlia/error.hpp
    ${CMAKE_SOURCE_DIR}/include/kademlia/session_base.hpp
    ${CMAKE_SOURCE_DIR}/include/kademlia/first_session.hpp
    ${CMAKE_SOURCE_DIR}/include/kademlia/session.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/session_impl.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/boost_to_std_error.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/buffer.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/concurrent_guard.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/constants.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/constants.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/endpoint.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/engine.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/error.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/error_impl.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/error_impl.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/find_value_task.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/id.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/id.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/ip_endpoint.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/ip_endpoint.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/log.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/log.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/network.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/message.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/message.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/message_serializer.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/message_serializer.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/message_socket.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/peer.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/peer.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/response_callbacks.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/response_callbacks.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/response_router.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/routing_table.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/session.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/session_base.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/first_session.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/store_value_task.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/discover_neighbors_task.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/timer.cpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/timer.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/tracker.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/value_store.hpp
    ${CMAKE_SOURCE_DIR}/src/kademlia/lookup_task.hpp)

set(first_peer_source
    first_peer.cpp
    ${kademlia_sources})

set(second_peer_source
    second_peer.cpp
    ${kademlia_sources})

set(CMAKE_BUILD_TYPE "Debug")

add_executable(first_peer ${first_peer_source})
add_executable(second_peer ${second_peer_source})

target_link_libraries(first_peer
    ${Boost_SYSTEM_LIBRARY}
    ${OPENSSL_CRYPTO_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(second_peer
    ${Boost_SYSTEM_LIBRARY}
    ${OPENSSL_CRYPTO_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT})