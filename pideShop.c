
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
#include <pthread.h>
#include <signal.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdatomic.h>
#include <math.h>

#define MAX_COOKS 100
#define MAX_DELIVERIES 100
#define MAX_OVEN_CAPACITY 6
#define MAX_DELIVERY_CAPACITY 3
#define BUFFER_SIZE 1024
#define MAX_ORDERS 10000
#define MAX_CLIENTS 10000
#define MAX_OVEN_QUEUE 10000
#define START_PORT 8080
#define END_PORT 9000

typedef struct {
    int id;
    int busy;
    int count;
} Cook;

typedef struct {
    int client_num;
    int pid;
    int x, y;
    int socket;
    int completed;
} Order;

typedef struct {
    int id;
    int busy;
    Order *deliveries[MAX_DELIVERY_CAPACITY];
    int delivery_count;
    float speed;
    int count;
} DeliveryPerson;

typedef struct {
    Order *orders[MAX_OVEN_QUEUE];
    int head;
    int tail;
    int count;
} OvenQueue;

// it takes 4m(n^2)+8(n^3) operations. So I will simulate that
// 4*30*(40^2)+8*(40^3) = 704000
void simulate_pseudo_inverse_time() {
    int i, j;
    long long num_operations = 704000;

    for (i = 0; i < num_operations; i++) {
        j++;
    }
}
void simulate_pseudo_inverse_time_half() {
    int i, j;
    long long num_operations = 352000;

    for (i = 0; i < num_operations; i++) {
        j++;
    }
}


OvenQueue ovenQueue = { .head = 0, .tail = 0, .count = 0 };
OvenQueue cookedOrderQueue = { .head = 0, .tail = 0, .count = 0 };


pthread_mutex_t oven_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t apparatus_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t delivery_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t order_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t client_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t oven_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cooked_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t oven_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t apparatus_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t order_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t delivery_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t oven_queue_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cooked_queue_cond = PTHREAD_COND_INITIALIZER;


Cook cooks[MAX_COOKS];
DeliveryPerson deliveryPersons[MAX_DELIVERIES];
Order orders[MAX_ORDERS];
int order_count = 0;
int order_head = 0;
int order_tail = 0;

int oven_count = 0;
int apparatus_count = 3;

FILE *logFile;

int client_sockets[MAX_CLIENTS];
int client_count = 0;

atomic_int stop = ATOMIC_VAR_INIT(0);

pthread_t ovenManagerThread;
pthread_t cookThreads[MAX_COOKS];
pthread_t deliveryThreads[MAX_DELIVERIES];


void log_message(const char *message) {
    pthread_mutex_lock(&log_mutex);
    fprintf(logFile, "%s\n", message);
    fflush(logFile);
    pthread_mutex_unlock(&log_mutex);
}

void signal_client(int client_socket, const char *message) {
    send(client_socket, message, strlen(message), 0);
}

void printOrderQueue() {
    int i;

    for (i = 0; i < MAX_ORDERS; i++) {
        if (orders[i].client_num > 0) {
            printf("Order%d----Completed:%d, Socket:%d\n", orders[i].client_num, orders[i].completed, orders[i].socket);
        }
    }
}

int isAllDeliveryDone(Order currOrder) {
    for (int i = 0; i < MAX_ORDERS; i++) {
        if (orders[i].socket == currOrder.socket && orders[i].completed == 0) {
            return 0;
        }
    }
    return 1;
}

void *oven_manager_function(void *arg) {
    while (atomic_load(&stop) == 0) {
        pthread_mutex_lock(&oven_queue_mutex);
        while (ovenQueue.count == 0 && atomic_load(&stop) == 0) {
            pthread_cond_wait(&oven_queue_cond, &oven_queue_mutex);
        }

        if (atomic_load(&stop)) {
            pthread_mutex_unlock(&oven_queue_mutex);
            break;
        }

        Order *order = ovenQueue.orders[ovenQueue.head];
        ovenQueue.head = (ovenQueue.head + 1) % MAX_OVEN_QUEUE;
        ovenQueue.count--;

        pthread_mutex_unlock(&oven_queue_mutex);

        if (order->completed == -1) {
            continue;
        }

        pthread_mutex_lock(&oven_mutex);
        while (oven_count == MAX_OVEN_CAPACITY && atomic_load(&stop) == 0) {
            pthread_cond_wait(&oven_cond, &oven_mutex);
        }

        if (atomic_load(&stop)) {
            pthread_mutex_unlock(&oven_mutex);
            break;
        }

        oven_count++;
        pthread_mutex_unlock(&oven_mutex);

        char log_msg[BUFFER_SIZE];
        snprintf(log_msg, BUFFER_SIZE, "Order from client %d is now being cooked in the oven...", order->client_num);
        log_message(log_msg);

        simulate_pseudo_inverse_time_half();

        snprintf(log_msg, BUFFER_SIZE, "Order %d (PID %d) cooked.\n", order->client_num, order->pid);
        log_message(log_msg);
        signal_client(order->socket, log_msg);

        pthread_mutex_lock(&oven_mutex);
        oven_count--;
        pthread_cond_signal(&oven_cond);
        pthread_mutex_unlock(&oven_mutex);

        pthread_mutex_lock(&cooked_queue_mutex);
        cookedOrderQueue.orders[cookedOrderQueue.tail] = order;
        cookedOrderQueue.tail = (cookedOrderQueue.tail + 1) % MAX_OVEN_QUEUE;
        cookedOrderQueue.count++;
        pthread_cond_signal(&cooked_queue_cond);
        pthread_mutex_unlock(&cooked_queue_mutex);
    }
    return NULL;
}

void *cook_function(void *arg) {
    Cook *cook = (Cook *)arg;

    while (atomic_load(&stop) == 0) {
        pthread_mutex_lock(&order_mutex);
        while (order_count == 0 && atomic_load(&stop) == 0) {
            pthread_cond_wait(&order_cond, &order_mutex);
        }

        if (atomic_load(&stop)) {
            pthread_mutex_unlock(&order_mutex);
            break;
        }

        Order *order = &orders[order_head];
        order_head = (order_head + 1) % MAX_ORDERS;
        order_count--;

        pthread_mutex_unlock(&order_mutex);

        if (order->completed == -1) {
            continue;
        }

        cook->busy = 1;
        cook->count++;
        char log_msg[BUFFER_SIZE];

        if (atomic_load(&stop) == 0) {
            snprintf(log_msg, BUFFER_SIZE, "Cook %d is preparing an order from client %d...", cook->id, order->client_num);
            log_message(log_msg);
        }

        // sleep(3); // Simulate preparation time
        simulate_pseudo_inverse_time();

        if (atomic_load(&stop) == 0) {
            snprintf(log_msg, BUFFER_SIZE, "Cook %d has prepared an order from client %d (PID %d)...\n", cook->id, order->client_num, order->pid);
            signal_client(order->socket, log_msg);
            log_message(log_msg);
        }
        

        pthread_mutex_lock(&oven_queue_mutex);
        ovenQueue.orders[ovenQueue.tail] = order;
        ovenQueue.tail = (ovenQueue.tail + 1) % MAX_OVEN_QUEUE;
        ovenQueue.count++;
        pthread_cond_signal(&oven_queue_cond);
        pthread_mutex_unlock(&oven_queue_mutex);

        cook->busy = 0;
    }
    return NULL;
}

void print_max_count_info() {
    int maxCookCount = -1;
    Cook *maxCook = NULL;
    
    int maxDeliveryCount = -1;
    DeliveryPerson *maxDeliveryPerson = NULL;
    
    for (int i = 0; i < MAX_COOKS; i++) {
        if (cooks[i].count > maxCookCount) {
            maxCookCount = cooks[i].count;
            maxCook = &cooks[i];
        }
    }
    
    for (int i = 0; i < MAX_DELIVERIES; i++) {
        if (deliveryPersons[i].count > maxDeliveryCount) {
            maxDeliveryCount = deliveryPersons[i].count;
            maxDeliveryPerson = &deliveryPersons[i];
        }
    }
    
    char log_msg[BUFFER_SIZE];
    
    if (maxCook != NULL && maxDeliveryPerson != NULL) {
        snprintf(log_msg, BUFFER_SIZE, "Thanks Cook %d and Moto %d", maxCook->id, maxDeliveryPerson->id);
    }
    
    log_message(log_msg);
}

void *delivery_function(void *arg) {
    DeliveryPerson *deliveryPerson = (DeliveryPerson *)arg;

    while (atomic_load(&stop) == 0) {
        pthread_mutex_lock(&cooked_queue_mutex);

        while (deliveryPerson->delivery_count < MAX_DELIVERY_CAPACITY && cookedOrderQueue.count > 0 && atomic_load(&stop) == 0) {
            // Get an order from the cooked orders queue
            Order *order = cookedOrderQueue.orders[cookedOrderQueue.head];
            cookedOrderQueue.head = (cookedOrderQueue.head + 1) % MAX_OVEN_QUEUE;
            cookedOrderQueue.count--;

            // Add the order to the delivery person's deliveries
            deliveryPerson->deliveries[deliveryPerson->delivery_count++] = order;
            deliveryPerson->count++;

            char msmg[BUFFER_SIZE];

            snprintf(msmg, BUFFER_SIZE, "Order %d (PID %d) is handed to Delivery Personel %d\n", order->client_num, order->pid, deliveryPerson->id);
            log_message(msmg);
            signal_client(order->socket, msmg);
        }

        if (atomic_load(&stop)) {
            pthread_mutex_unlock(&cooked_queue_mutex);
            break;
        }

        if (deliveryPerson->delivery_count == 0) {
            pthread_cond_wait(&cooked_queue_cond, &cooked_queue_mutex);
        }

        pthread_mutex_unlock(&cooked_queue_mutex);

        if (deliveryPerson->delivery_count > 0) {
            // Calculate total delivery distance
            float total_delivery_distance = 0.0;
            for (int i = 0; i < deliveryPerson->delivery_count; i++) {
                Order *order = deliveryPerson->deliveries[i];
                if (order->completed == -1) {
                    continue;
                }

                float dx = order->x - (i == 0 ? 0 : deliveryPerson->deliveries[i - 1]->x);
                float dy = order->y - (i == 0 ? 0 : deliveryPerson->deliveries[i - 1]->y);
                float distance = sqrt(dx * dx + dy * dy);
                total_delivery_distance += distance;
            }

            float delivery_time = total_delivery_distance / deliveryPerson->speed;

            Order *last_order = deliveryPerson->deliveries[deliveryPerson->delivery_count - 1];
            float return_distance = sqrt(last_order->x * last_order->x + last_order->y * last_order->y);
            float return_time = return_distance / deliveryPerson->speed;

            char log_msg[BUFFER_SIZE];

            if (atomic_load(&stop) == 0) {
                snprintf(log_msg, BUFFER_SIZE, "Delivery Person %d is making deliveries...", deliveryPerson->id);
                log_message(log_msg);
            }
            int delivery_count = deliveryPerson->delivery_count;
            Order *deliveries[MAX_DELIVERY_CAPACITY];
            for (int i = 0; i < delivery_count; i++) {
                deliveries[i] = deliveryPerson->deliveries[i];
            }
            deliveryPerson->delivery_count = 0;

            for (int i = 0; i < delivery_count; i++) {
                Order *order = deliveries[i];
                if (order->completed == -1) {
                    continue;
                }
                int all_completed = 1;

                pthread_mutex_lock(&order_mutex);
                order->completed = 1;

                all_completed = isAllDeliveryDone(*order);
                pthread_mutex_unlock(&order_mutex);
                if (all_completed) {
                    sleep((int)delivery_time); // delivery time
                    pthread_mutex_lock(&order_mutex);
                    signal_client(order->socket, "All orders completed");

                    printf("done serving client @ XXX PID %d\n", order->pid);
                    print_max_count_info();
                    snprintf(log_msg, BUFFER_SIZE, "done serving client @ XXX PID %d", order->pid);
                    log_message(log_msg);

                    pthread_mutex_unlock(&order_mutex);
                }
            }
            sleep((int)return_time); // return time
            snprintf(log_msg, BUFFER_SIZE, "Delivery Person %d has returned from deliveries...", deliveryPerson->id);
            log_message(log_msg);
        }
    }
    return NULL;
}
void cancelOrders(int client_socket) {
    int i;

    for (i = 0; i < MAX_ORDERS; i++) {
        if (orders[i].socket == client_socket) {
            orders[i].completed = -1; // -1 for canceled order
        }
    }
}


void *client_handler(void *arg) {
    int client_socket = *(int *)arg;
    free(arg);

    char buffer[BUFFER_SIZE];
    int valread;
    char *order_token;

    pthread_mutex_lock(&client_mutex);
    client_sockets[client_count++] = client_socket;
    pthread_mutex_unlock(&client_mutex);

    while ((valread = read(client_socket, buffer, BUFFER_SIZE - 1)) > 0 && atomic_load(&stop) == 0) {
        buffer[valread] = '\0';
        if (strstr(buffer, "Orders canceled") != NULL) {
            int pid = 0;
            if (sscanf(buffer, "Orders canceled (PID: %d)", &pid) == 1) {
                printf(">> order cancelled @YYY PID: %d\n", pid);
                char log_msg[BUFFER_SIZE];
                snprintf(log_msg, BUFFER_SIZE, "Orders canceled, PID: %d", pid);
                log_message(log_msg);
                cancelOrders(client_socket);
                break;
            } else {
                break;
            }
        }
        order_token = strtok(buffer, "\n");
        int count = 0;
        while (order_token != NULL) {
            count++;
            log_message(order_token);

            Order order;
            sscanf(order_token, "Order from client %d (PID: %d) at location (%d, %d)", &order.client_num, &order.pid, &order.x, &order.y);

            char message[256];
            sprintf(message, ">> Pideci: Order from client %d (PID: %d) at location (%d, %d) placed.\n", order.client_num, order.pid, order.x, order.y);
            signal_client(client_socket, message);

            order.socket = client_socket;
            order.completed = 0;

            pthread_mutex_lock(&order_mutex);
            if (order_count < MAX_ORDERS) {
                orders[order_tail] = order;
                order_tail = (order_tail + 1) % MAX_ORDERS;
                order_count++;
                pthread_cond_broadcast(&order_cond); 
            } else {
                printf("Order queue is full. Unable to add order from client %d\n", order.client_num);
            }
            pthread_mutex_unlock(&order_mutex);

            order_token = strtok(NULL, "\n");
        }
        printf(">> %d new customers.. Serving\n", count);
    }

    close(client_socket);
    return NULL;
}

void signal_handler(int sig) {
    atomic_store(&stop, 1);
    log_message("^C.. quitting.. writing log file");
    printf("^C.. quitting.. writing log file\n");

    pthread_cond_broadcast(&order_cond);
    pthread_cond_broadcast(&delivery_cond);
    pthread_cond_broadcast(&oven_cond);
    pthread_cond_broadcast(&apparatus_cond);
    pthread_cond_broadcast(&oven_queue_cond);
    pthread_cond_broadcast(&cooked_queue_cond);
    
    for (int i = 0; i < client_count; i++) {
        signal_client(client_sockets[i], "Server is shutting down");
        close(client_sockets[i]);
    }

    pthread_join(ovenManagerThread, NULL);
    for (int i = 0; i < MAX_COOKS; i++) {
        pthread_join(cookThreads[i], NULL);
    }
    for (int i = 0; i < MAX_DELIVERIES; i++) {
        pthread_join(deliveryThreads[i], NULL);
    }

    fclose(logFile);
    
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s [IPAddress] [CookPoolSize] [DeliveryPoolSize] [speed]\n", argv[0]);
        exit(1);
    }

    char *ip_address = argv[1];
    int cookPoolSize = atoi(argv[2]);
    int deliveryPoolSize = atoi(argv[3]);
    float speed = atof(argv[4]);

    logFile = fopen("pideShop.log", "w");
    if (logFile == NULL) {
        perror("Could not open log file");
        exit(1);
    }

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    printf("PideShop %s %d %d %f\n", ip_address, cookPoolSize, deliveryPoolSize, speed);
    log_message("PideShop active waiting for connection...");
    
    for (int i = 0; i < cookPoolSize; i++) {
        cooks[i].id = i + 1;
        cooks[i].busy = 0;
        cooks[i].count = 0;
    }

    for (int i = 0; i < deliveryPoolSize; i++) {
        deliveryPersons[i].id = i + 1;
        deliveryPersons[i].busy = 0;
        deliveryPersons[i].delivery_count = 0;
        deliveryPersons[i].speed = speed;
        deliveryPersons[i].count = 0;
    }

    pthread_create(&ovenManagerThread, NULL, oven_manager_function, NULL);

    for (int i = 0; i < cookPoolSize; i++) {
        pthread_create(&cookThreads[i], NULL, cook_function, &cooks[i]);
    }

    for (int i = 0; i < deliveryPoolSize; i++) {
        pthread_create(&deliveryThreads[i], NULL, delivery_function, &deliveryPersons[i]);
    }

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int port = START_PORT;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(1);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_address);

    while (port <= END_PORT) {
        address.sin_port = htons(port);
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == 0) {
            break;
        }
        port++;
    }

    if (port > END_PORT) {
        perror("No available ports");
        exit(1);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(1);
    }

    printf("Listening on %s:%d\n", ip_address, port);
    log_message("Listening on port...");
    printf("> > PideShop active waitng for connection ...\n");
    log_message("PideShop active waitng for connection ...");

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            exit(1);
        }

        printf("New connection established.\n");

        pthread_t clientThread;
        int *client_socket = malloc(sizeof(int));
        *client_socket = new_socket;
        pthread_create(&clientThread, NULL, client_handler, client_socket);
        pthread_detach(clientThread);
    }

    fclose(logFile);
    return 0;
}