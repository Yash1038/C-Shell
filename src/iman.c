#include "../include/headers.h"

void iMan(char *command_name)
{

    struct hostent *he;
    
    (struct hostent *)malloc(sizeof(struct hostent));

    he = gethostbyname("man.he.net");
    if (he == NULL)
    {
        perror("gethostbyname");
        return;
    }

    int sockfd;
    struct sockaddr_in server_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return;
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)he->h_addr_list[0], (char *)&server_addr.sin_addr.s_addr, he->h_length);
    server_addr.sin_port = htons(80);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        return;
    }

    char req[128] = "GET /?topic=";
    strcat(req, command_name);
    char *tmp = "&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n";
    strcat(req, tmp);

    if (send(sockfd, req, strlen(req), 0) < 0)
    {
        perror("send");
        return;
    }

    char *buffer = (char *)malloc(1024);
    ssize_t n;
    char * response = (char *)malloc(100000);

    while ((n = recv(sockfd, buffer, 1024, 0)) > 0)
    {
        buffer[n] = '\0';
        strcat(response, buffer);
        
    }

    char *start = strstr(response, "NAME\n");
    char *end = strstr(response, "AUTHOR\n");
    printf("%.*s", (int)(end - start), start);


    if (n < 0)
    {
        perror("recv");
        return;
    }

    free(buffer);

    close(sockfd);
}
