
//           _____                _____                    _____                    _____                    _____                    _____                            _____                    _____                    _____                _____          
//          /\    \              /\    \                  /\    \                  /\    \                  /\    \                  /\    \                          /\    \                  /\    \                  /\    \              /\    \         
//         /::\    \            /::\    \                /::\    \                /::\____\                /::\    \                /::\____\                        /::\____\                /::\____\                /::\    \            /::\    \        
//        /::::\    \           \:::\    \              /::::\    \              /:::/    /               /::::\    \              /::::|   |                       /:::/    /               /:::/    /               /::::\    \           \:::\    \       
//       /::::::\    \           \:::\    \            /::::::\    \            /:::/    /               /::::::\    \            /:::::|   |                      /:::/    /               /:::/    /               /::::::\    \           \:::\    \      
//      /:::/\:::\    \           \:::\    \          /:::/\:::\    \          /:::/    /               /:::/\:::\    \          /::::::|   |                     /:::/    /               /:::/    /               /:::/\:::\    \           \:::\    \     
//     /:::/__\:::\    \           \:::\    \        /:::/__\:::\    \        /:::/____/               /:::/__\:::\    \        /:::/|::|   |                    /:::/____/               /:::/    /               /:::/__\:::\    \           \:::\    \    
//    /::::\   \:::\    \          /::::\    \      /::::\   \:::\    \      /::::\    \              /::::\   \:::\    \      /:::/ |::|   |                   /::::\    \              /:::/    /               /::::\   \:::\    \          /::::\    \   
//   /::::::\   \:::\    \        /::::::\    \    /::::::\   \:::\    \    /::::::\____\________    /::::::\   \:::\    \    /:::/  |::|   | _____            /::::::\____\________    /:::/    /      _____    /::::::\   \:::\    \        /::::::\    \  
//  /:::/\:::\   \:::\    \      /:::/\:::\    \  /:::/\:::\   \:::\    \  /:::/\:::::::::::\    \  /:::/\:::\   \:::\    \  /:::/   |::|   |/\    \          /:::/\:::::::::::\    \  /:::/____/      /\    \  /:::/\:::\   \:::\____\      /:::/\:::\    \ 
// /:::/  \:::\   \:::\____\    /:::/  \:::\____\/:::/  \:::\   \:::\____\/:::/  |:::::::::::\____\/:::/  \:::\   \:::\____\/:: /    |::|   /::\____\        /:::/  |:::::::::::\____\|:::|    /      /::\____\/:::/  \:::\   \:::|    |    /:::/  \:::\____\
// \::/    \:::\  /:::/    /   /:::/    \::/    /\::/    \:::\  /:::/    /\::/   |::|~~~|~~~~~     \::/    \:::\  /:::/    /\::/    /|::|  /:::/    /        \::/   |::|~~~|~~~~~     |:::|____\     /:::/    /\::/   |::::\  /:::|____|   /:::/    \::/    /
//  \/____/ \:::\/:::/    /   /:::/    / \/____/  \/____/ \:::\/:::/    /  \/____|::|   |           \/____/ \:::\/:::/    /  \/____/ |::| /:::/    /          \/____|::|   |           \:::\    \   /:::/    /  \/____|:::::\/:::/    /   /:::/    / \/____/ 
//           \::::::/    /   /:::/    /                    \::::::/    /         |::|   |                    \::::::/    /           |::|/:::/    /                 |::|   |            \:::\    \ /:::/    /         |:::::::::/    /   /:::/    /          
//            \::::/    /   /:::/    /                      \::::/    /          |::|   |                     \::::/    /            |::::::/    /                  |::|   |             \:::\    /:::/    /          |::|\::::/    /   /:::/    /           
//            /:::/    /    \::/    /                       /:::/    /           |::|   |                     /:::/    /             |:::::/    /                   |::|   |              \:::\__/:::/    /           |::| \::/____/    \::/    /            
//           /:::/    /      \/____/                       /:::/    /            |::|   |                    /:::/    /              |::::/    /                    |::|   |               \::::::::/    /            |::|  ~|           \/____/             
//          /:::/    /                                    /:::/    /             |::|   |                   /:::/    /               /:::/    /                     |::|   |                \::::::/    /             |::|   |                               
//         /:::/    /                                    /:::/    /              \::|   |                  /:::/    /               /:::/    /                      \::|   |                 \::::/    /              \::|   |                               
//         \::/    /                                     \::/    /                \:|   |                  \::/    /                \::/    /                        \:|   |                  \::/____/                \:|   |                               
//          \/____/                                       \/____/                  \|___|                   \/____/                  \/____/                          \|___|                   ~~                       \|___|                               


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

#define DEFAULT_PORT 8080

int sock = 0;
pid_t pid;

void signal_handler(int sig) {
    if (sig == SIGINT || sig == SIGTERM) {
        printf(">> ^C signal .. cancelling orders.. editing log..\n");
        
        char cancel_msg[50];
        sprintf(cancel_msg, "Orders canceled (PID: %d)", pid);
        send(sock, cancel_msg, strlen(cancel_msg), 0);
        
        close(sock);
        exit(0);
    }
}

void send_order(int client_num, int x, int y, pid_t pid) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "Order from client %d (PID: %d) at location (%d, %d)\n", client_num, pid, x, y);
    send(sock, buffer, strlen(buffer), 0);
    printf("Order placed: %s", buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s [IPAddress[:port]] [numberOfClients] [p] [q]\n", argv[0]);
        return -1;
    }

    char *ip_address = argv[1];
    int numberOfClients = atoi(argv[2]);
    int p = atoi(argv[3]);
    int q = atoi(argv[4]);

    char *colon_ptr = strchr(ip_address, ':');
    int port = DEFAULT_PORT;
    if (colon_ptr != NULL) {
        *colon_ptr = '\0'; 
        port = atoi(colon_ptr + 1);
    }

    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip_address, &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    printf(">> Connected to the PideShop server at %s:%d.\n", ip_address, port);

    srand(time(NULL));
    pid = getpid();
    for (int i = 0; i < numberOfClients; i++) {
        int x = rand() % p;
        int y = rand() % q;

        send_order(i + 1, x, y, pid);
    }
    printf(">> PID %d..\n", pid);
    printf(">> ...\n");

    while (1) {
        int valread = read(sock, buffer, sizeof(buffer) - 1);
        if (valread > 0) {
            buffer[valread] = '\0';
            if (strstr(buffer, "All orders completed") != NULL) {
                printf(">> All customers served\n");
                break;
            } else if (strstr(buffer, "Server is shutting down") != NULL) {
                printf(">> Shop closed! Exiting...\n");
                break;
            } else {
                printf("%s\n", buffer);
            }
        }
        sleep(1);
    }
    printf(">> log file written ..\n");
    close(sock);

    return 0;
}
