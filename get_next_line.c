#include "get_next_line.h"

char *get_next_line(int fd) {
  if (BUFFER_SIZE < 1 || fd < 0)
    return (NULL);

  char *buffer = malloc(BUFFER_SIZE + 1);
  if (!buffer)
    return NULL;

  static char *leftover;
  ssize_t bytes_read = 1;

  if (!leftover)
    leftover = ft_strdup("");

  while (!ft_strchr(leftover, '\n')) {
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read <= 0)
      break;
    buffer[bytes_read] = '\0';
    char *tmp = leftover;
    leftover = ft_strjoin(leftover, buffer);
    if (!leftover) {
      return (NULL);
    }
    free(tmp);
  }

  if (leftover[0] == '\0') {
    free(leftover);
    leftover = NULL;
    free(buffer);
    return (NULL);
  }

  size_t len = 0;
  while (leftover[len] && leftover[len] != '\n')
    len++;
  if (leftover[len] == '\n')
    len++;

  char *next_line = malloc(len + 1);
  if (!next_line)
    return (NULL);

  size_t i = 0;
  while (i < len) {
    next_line[i] = leftover[i];
    i++;
  }

  next_line[i] = '\0';

  char *new_leftover = ft_strdup(&leftover[len]);
  free(leftover);
  leftover = new_leftover;

  free(buffer);

  return (next_line);
}

// int main() {
//   // int fd = open("tests/text.txt", O_RDONLY);
//   int fd = open("tests/big_line_with_nl", O_RDONLY);
//   char *next_line;
//   next_line = get_next_line(fd);
//   printf("%s", next_line);
//   free(next_line);

//   next_line = get_next_line(fd);
//   printf("%s", next_line);
//   free(next_line);

//   next_line = get_next_line(fd);
//   printf("%s", next_line);
//   free(next_line);

//   next_line = get_next_line(fd);
//   printf("%s", next_line);
//   free(next_line);
//   next_line = get_next_line(fd);
//   printf("%s", next_line);
//   free(next_line);
//   next_line = get_next_line(fd);
//   printf("%s", next_line);
//   free(next_line);
//   next_line = get_next_line(fd);
//   printf("%s \n", next_line);
//   free(next_line);
// }
