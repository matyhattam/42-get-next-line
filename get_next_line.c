#include "get_next_line.h"

char *create_nl(const char *leftover) {
  size_t len = 0;
  while (leftover[len] && leftover[len] != '\n')
    len++;
  if (leftover[len] == '\n')
    len++;

  char *new_line = malloc(len + 1);
  if (!new_line)
    return (NULL);

  ft_memcpy(new_line, leftover, len);
  new_line[len] = '\0';

  return (new_line);
}

char *search_eol(int fd, char *buffer, char *leftover) {
  while (!ft_strchr(leftover, '\n')) {
    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read <= 0)
      break;
    buffer[bytes_read] = '\0';
    char *tmp = leftover;
    leftover = ft_strjoin(leftover, buffer);
    if (!leftover) {
      free(tmp);
      return (NULL);
    }
    free(tmp);
  }
  return (leftover);
}

char *guard_eof(char *leftover) {
  if (leftover[0] == '\0') {
    free(leftover);
    leftover = NULL;
    return (NULL);
  }
  return (leftover);
}

char *get_next_line(int fd) {
  if (BUFFER_SIZE < 1 || fd < 0)
    return (NULL);

  char *buffer = malloc(BUFFER_SIZE + 1);
  if (!buffer)
    return NULL;

  static char *leftover;
  if (!leftover)
    leftover = ft_strdup("");

  leftover = search_eol(fd, buffer, leftover);
  if (!leftover) {
    free(buffer);
    return (NULL);
  }

  leftover = guard_eof(leftover);
  if (!leftover) {
    free(buffer);
    return (NULL);
  }

  char *next_line = create_nl(leftover);
  if (!leftover) {
    free(buffer);
    return (NULL);
  }

  size_t len = ft_strlen(next_line);
  char *new_leftover = ft_strdup(&leftover[len]);
  if (!new_leftover) {
    free(leftover);
    free(next_line);
    free(buffer);
    return (NULL);
  }

  free(leftover);
  leftover = new_leftover;
  free(buffer);

  return (next_line);
}

// int main() {
//   int fd = open("tests/text.txt", O_RDONLY);
//   // int fd = open("tests/big_line_with_nl", O_RDONLY);
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
