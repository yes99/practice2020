      else if(idx == 1){ // upload
         if (0 < (fd = open("mytext.pdf", O_RDONLY))) {
            strcpy(tmp, c_buf); // tmp = "FLAG_UPLOAD|2016112645|"

            //while (tmp == NULL) // 반복문 적용하려고 했는데 일단 보류하고 한번만 읽는걸로 테스트
            //{
               read(fd, data, 200);
               strcat(tmp, data);
               printf("MSG : %s\n", tmp);
               write(sock_flag, tmp, sizeof(tmp));

               strcpy(tmp, c_buf);
            //}
            strcpy(tmp, "FLAG_UPLOAD|2016112645|EOF");
            printf("MSG : %s\n", tmp);
            write(sock_flag, tmp, sizeof(tmp));

            read(sock_flag, s_buf, sizeof(s_buf));
            printf("%s\n", s_buf);

            close(fd);
         }
         else {
            printf("Failed to Open File...\n");
         }
      }