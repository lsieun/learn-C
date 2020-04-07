cmake_minimum_required(VERSION 3.15)
project(crypto C)

set(CMAKE_C_STANDARD 99)

add_executable(crypto main.c)

add_executable(http http/http.c)

add_executable(math math/math.c math/huge.c)

add_executable(hex-test utils/hex_test.c)

add_executable(rsa rsa/rsa.c)
add_executable(rsa-test-a rsa/rsa_test_a.c)
add_executable(rsa-test-b rsa/rsa_test_b_encryption.c)
add_executable(rsa-test-c rsa/rsa_test_c_decryption.c)
add_executable(rsa-test-d rsa/rsa_test_d_cipher.c)
add_executable(rsa-test rsa/rsa_test.c)


add_executable(dh-server dh/dh_server.c)
add_executable(dh-client dh/dh_client.c)

add_executable(ecc-app ecc/ecc_app.c)
add_executable(dsa-app dsa/dsa_app.c)
