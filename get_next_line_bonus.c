#include "get_next_line_bonus.h"

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

char *guard_eof(char *leftover) {
  if (leftover[0] == '\0') {
    free(leftover);
    leftover = NULL;
    return (NULL);
  }
  return (leftover);
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

  leftover = guard_eof(leftover);
  if (!leftover) {
    return (NULL);
  }

  return (leftover);
}

char *shift_and_free(char *leftover, char *next_line, char *buffer,
                     size_t len) {
  char *new_leftover = ft_strdup(&leftover[len]);
  if (!new_leftover) {
    free(leftover);
    free(next_line);
    free(buffer);
    return (NULL);
  }

  free(leftover);
  free(buffer);
  return (new_leftover);
}

char *get_next_line(int fd) {
  if (BUFFER_SIZE < 1 || fd < 0)
    return (NULL);

  char *buffer = malloc(BUFFER_SIZE + 1);
  if (!buffer)
    return NULL;

  static char *leftover[MAX_FD];
  if (!leftover[fd])
    leftover[fd] = ft_strdup("");

  leftover[fd] = search_eol(fd, buffer, leftover[fd]);
  if (!leftover[fd]) {
    free(buffer);
    return (NULL);
  }

  char *next_line = create_nl(leftover[fd]);
  if (!next_line) {
    free(buffer);
    return (NULL);
  }

  size_t len = ft_strlen(next_line);
  leftover[fd] = shift_and_free(leftover[fd], next_line, buffer, len);
  if (!leftover[fd])
    return (NULL);

  return (next_line);
}

// int main() {
//   int fd1 = open("tests/text.txt", O_RDONLY);
//   int fd2 = open("tests/text.txt", O_RDONLY);
//   // int fd = open("tests/big_line_with_nl", O_RDONLY);
//   char *next_line;
//   next_line = get_next_line(fd1);
//   printf("%s", next_line);
//   free(next_line);

//   next_line = get_next_line(fd1);
//   printf("%s", next_line);
//   free(next_line);

//   next_line = get_next_line(fd2);
//   printf("%s", next_line);
//   free(next_line);

//   next_line = get_next_line(fd1);
//   printf("%s", next_line);
//   free(next_line);
//   next_line = get_next_line(fd2);
//   printf("%s", next_line);
//   free(next_line);
// next_line = get_next_line(fd);
// printf("%s", next_line);
// free(next_line);
// next_line = get_next_line(fd);
// printf("%s \n", next_line);
// free(next_line);
// }
