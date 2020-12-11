while (1) {
      idx = -1;
      memset(buf, 0x00, MAX);
      memset(data, 0x00, 200);
      printf("==============================\n");
      printf("0 : chat, 1 : upload, 2 : download, 3 : list_user, 4 : list_file, 5 : exit\n");
      printf(">>>");
      scanf("%d", &idx);
      getchar();

      strcat(buf, flag[idx]);
      strcat(buf, "|");
      strcat(buf, user);
      strcat(buf, "|");

      else if(idx == 1){ // upload
         if (0 < (fd = open("mytext.pdf", O_RDONLY))) {
            memset(buf, 0x00, MAX);
            strcpy(tmp, buf); // tmp = "FLAG_UPLOAD|2016112645|"

            //while (tmp == NULL) // 반복문 적용하려고 했는데 일단 보류하고 한번만 읽는걸로 테스트
            //{
               read(fd, data, 200);
               strcat(tmp, data);
               printf("MSG : %s\n", tmp);
               write(sock_flag, tmp, sizeof(tmp));

            
            //}
            strcpy(tmp, "FLAG_UPLOAD|2016112645|EOF");
            printf("MSG : %s\n", tmp);
            write(sock_flag, tmp, sizeof(tmp));

            read(sock_flag, buf, sizeof(buf));
            printf("%s\n", buf);

            close(fd);
         }
         else {
            printf("Failed to Open File...\n");
         }
      }
}