      else if(idx == 2){ // download
         char file[50];
         printf("File Name : ");
         scanf("%s", file);
         strcat(buf, file);

         if (0 > (fd = open(file, O_WRONLY | O_CREAT,0644)))
         {
            printf("Failed to Open File...\n");
            break; // 이게 실행 될일은 없겠지만 브뤡 하면 프로그램 자체 종료됨 ㅋㅋ
         }

         write(sock_flag, buf, sizeof(buf));
         memset(buf, 0x00, MAX);

         while(read(sock_flag, buf, sizeof(buf)) >0);  // HS :: 요청을 했을때 
        {
         s[0] = strtok(buf, "|"); // flag
         s[1] = strtok(NULL, "|"); // user
         s[2] = strtok(NULL, "|"); // file
         strcpy(s_file, s[2]);

         write(fd, s_file, strlen(s_file));

         printf("%s\n", s_data);
        }
         read(sock_flag, buf, sizeof(buf));  // ???????? 뭘 읽어오겠다는거? EOF
         s[0] = strtok(buf, "|"); // flag
         s[1] = strtok(NULL, "|"); // user
         s[2] = strtok(NULL, "|"); // file
         strcpy(s_file, s[2]);
         printf("%s\n", s_data);
      
         close(fd);
      }