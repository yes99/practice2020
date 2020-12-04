      else if(idx == 2){ // download
         printf("File Name : ");
         scanf("%s", data);
         strcat(buf, data);

         if (0 > (fd = open(data, O_WRONLY | O_CREAT,0644)))
         {
            printf("Failed to Open File...\n");
            break;
         }

         write(sock_flag, buf, sizeof(buf));
         memset(buf, 0x00, MAX);
         read(sock_flag, buf, sizeof(buf));

         s[0] = strtok(buf, "|"); // flag
         s[1] = strtok(NULL, "|"); // user
         s[2] = strtok(NULL, "|"); // data
         strcpy(s_data, s[2]);

         write(fd, s_data, strlen(s_data));

         printf("%s\n", s_data);

         read(sock_flag, buf, sizeof(buf));
         s[0] = strtok(buf, "|"); // flag
         s[1] = strtok(NULL, "|"); // user
         s[2] = strtok(NULL, "|"); // data
         strcpy(s_data, s[2]);
         printf("%s\n", s_data);
      
         close(fd);
      }