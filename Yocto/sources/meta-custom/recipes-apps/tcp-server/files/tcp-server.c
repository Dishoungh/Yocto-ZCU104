#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_COMMAND_SIZE    128
#define MAX_RESPONSE_SIZE   128
#define MAX_CLIENTS         5
#define PORT                3000
#define IP_SIZE             0x10000
#define BTN_GPIO            "/dev/uio0"
#define DIP_GPIO            "/dev/uio1"
#define LED_GPIO            "/dev/uio2"

volatile uint32_t read_reg(char* path, unsigned offset)
{
    int fd = open(path, O_RDONLY | O_SYNC);

    if (fd < 0)
    {
        perror("open failed");
        return 0;
    }

    void* mem_ptr = mmap(NULL, IP_SIZE, PROT_READ, MAP_SHARED, fd, 0);

    if (mem_ptr == MAP_FAILED)
    {
        perror("mmap failed");
        close(fd);
        return 0;
    }

    volatile uint32_t data = *((volatile uint32_t *)(mem_ptr + offset));

    if (munmap(mem_ptr, IP_SIZE))
    {
        perror("munmap failed");
        close(fd);
        return 0;
    }

    close(fd);

    return data;
}

void write_reg(char* path, unsigned offset, volatile uint32_t data)
{
    int fd = open(path, O_RDWR | O_SYNC);

    if (fd < 0)
    {
        perror("open failed");
        return;
    }

    void* mem_ptr = mmap(NULL, IP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (mem_ptr == MAP_FAILED)
    {
        perror("mmap failed");
        close(fd);
        return;
    }

    *((volatile uint32_t *)(mem_ptr + offset)) = data;

    if (munmap(mem_ptr, IP_SIZE))
    {
        perror("munmap failed");
        close(fd);
        return;
    }

    close(fd);
}

void process_cmd(char* cmd, char* rsp)
{
    // This is a lazy command processor
    if (!strcmp(cmd, "BTN?"))
    {
        snprintf(rsp, MAX_RESPONSE_SIZE, "Buttons = %u\n", (read_reg(BTN_GPIO, 0x0) & 0xF));
    }
    else if (!strcmp(cmd, "DIP?"))
    {
        snprintf(rsp, MAX_RESPONSE_SIZE, "DIP Switches = %u\n", (read_reg(DIP_GPIO, 0x0) & 0xF));
    }
    else if (!strcmp(cmd, "LED?"))
    {
        snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs = %u\n", (read_reg(LED_GPIO, 0x0) & 0xF));
    }
    else if (!strcmp(cmd, "LED=0"))
    {
        volatile uint32_t value = 0;

        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=1"))
    {
        volatile uint32_t value = 1;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }   
    }
    else if (!strcmp(cmd, "LED=2"))
    {
        volatile uint32_t value = 2;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=3"))
    {
        volatile uint32_t value = 3;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=4"))
    {
        volatile uint32_t value = 4;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=5"))
    {
        volatile uint32_t value = 5;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=6"))
    {
        volatile uint32_t value = 6;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=7"))
    {
        volatile uint32_t value = 7;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=8"))
    {
        volatile uint32_t value = 8;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=9"))
    {
        volatile uint32_t value = 9;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=10"))
    {
        volatile uint32_t value = 10;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=11"))
    {
        volatile uint32_t value = 11;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=12"))
    {
        volatile uint32_t value = 12;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=13"))
    {
        volatile uint32_t value = 13;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=14"))
    {
        volatile uint32_t value = 14;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else if (!strcmp(cmd, "LED=15"))
    {
        volatile uint32_t value = 15;
        
        write_reg(LED_GPIO, 0x0, value);

        if ((read_reg(LED_GPIO, 0x0) & 0xF) != value)
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "Failed to set LED to %u\n", value);
        }
        else
        {
            snprintf(rsp, MAX_RESPONSE_SIZE, "LEDs set to %u\n", value);
        }
    }
    else // Unknown command
    {
        snprintf(rsp, MAX_RESPONSE_SIZE, "Error: Unknown command (%s)\n", cmd);
    }
}

int main()
{
    struct sockaddr_in server;
    struct sockaddr_in client;
    int socket_fd;
    int client_fd;
    uint8_t socket_opt = 1;

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

    // Create socket file descriptor for server
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        return 1;
    }
    else
    {
        printf("socket() successful\n");
    }

    // Configure socket options
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &socket_opt, sizeof(int)) < 0)
    {
        perror("setsockopt failed");
        return 2;
    }
    else
    {
        printf("setsockopt() successful\n");
    }

    // Configure TCP options
    server.sin_family = AF_INET;                // Use IPv4
    server.sin_port = htons(PORT);              // Set Port #
    server.sin_addr.s_addr = htonl(INADDR_ANY); // Set IP address to any available address

    // Bind socket to created socket object
    if ((bind(socket_fd, (struct sockaddr *) &server, sizeof(struct sockaddr))) < 0)
    {
        perror("bind failed");
        return 3;
    }
    else
    {
        printf("bind() successful\n");
    }

    // Listen for incoming connections
    if ((listen(socket_fd, MAX_CLIENTS)) < 0)
    {
        perror("listen failed");
        return 4;
    }
    else
    {
        printf("listen() successful\n");
    }

    while (1)
    {
        char command_buffer[MAX_COMMAND_SIZE] = {0};
        char response_buffer[MAX_RESPONSE_SIZE] = {0};

        socklen_t size = sizeof(struct sockaddr_in);
        printf("Waiting for a new client connection...\n");

        // Blocking wait (will wait until a client connects)
        while ((client_fd = accept(socket_fd, (struct sockaddr *) &client, &size)) == -1);

        printf("Server got connection from client %s\n", inet_ntoa(client.sin_addr));

        // Create pollfd
        struct pollfd pfd = {client_fd, POLLIN, 0};

        while (1)
        {
            printf("Waiting for a new command\n");

            if ((poll(&pfd, 1, -1) > 0) && (pfd.revents & POLLIN)) // For poll()>0, that means there's data available
            {
                ssize_t read_bytes = recv(client_fd, command_buffer, MAX_COMMAND_SIZE, 0);

                if (!read_bytes)
                {
                    printf("Connection aborted!\n");
                    break;
                }
                else if (read_bytes < 0)
                {
                    printf("Unknown read error at socket\n");
                    continue;
                }
                else
                {
                    // Remove trailing newline
                    command_buffer[strcspn(command_buffer, "\n")] = 0;
                    printf("Command received: %s\n", command_buffer);

                    // Process Command
                    process_cmd(command_buffer, response_buffer);
                    send(client_fd, response_buffer, strlen(response_buffer) + 1, 0);

                    // Clear command and response buffers
                    memset((void*) command_buffer, 0, MAX_COMMAND_SIZE);
                    memset((void*) response_buffer, 0, MAX_RESPONSE_SIZE);
                }
            }
        }

        close(client_fd);
    }
    close(socket_fd);

    return 0;
}