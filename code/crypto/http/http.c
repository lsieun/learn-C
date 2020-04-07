/**
* This test utility does simple (non-encrypted) HTTP.
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

/**
* Accept a well-formed URL (e.g. http://www.company.com/index.html) and return
* pointers to the host part and the path part. Note that this function
* modifies the uri itself as well. It returns 0 on success, -1 if the URL is
* found to be malformed in any way.
*/
int parse_url(char *uri, char **host, char **path) {
    char *pos;
}

int main(void) {
    //
}
