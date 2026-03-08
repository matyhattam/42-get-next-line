#include "get_next_line.h"

size_t ft_strlen(const char *s) {
  size_t i = 0;

  while (s[i] != 0) {
    i++;
  }

  return (i);
}

char *ft_strchr(const char *s, int c) {
  size_t i = 0;

  while (s[i]) {
    if (s[i] == c) {
      return ((char *)&s[i]);
    }
    i++;
  }

  if (s[i] == (char)c)
    return ((char *)&s[i]);

  return (NULL);
}

size_t ft_strlcpy(char *dest, const char *src, size_t size) {
  size_t i = 0;

  if (size == 0)
    return (ft_strlen(src));

  while (i < size - 1 && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }

  dest[i] = '\0';
  return (ft_strlen(src));
}

size_t ft_strlcat(char *dest, const char *src, size_t size) {
  size_t i = 0;
  size_t dest_len = ft_strlen(dest);
  size_t src_len = ft_strlen(src);

  if (size <= dest_len) {
    return (size + src_len);
  }

  while (src[i] != '\0' && (dest_len + i) < (size - 1)) {
    dest[dest_len + i] = src[i];
    i++;
  }

  dest[dest_len + i] = '\0';
  return (dest_len + src_len);
}

char *ft_strjoin(char const *s1, char const *s2) {
  if (!s1 || !s2)
    return (NULL);

  size_t s1_len = ft_strlen(s1);
  size_t s2_len = ft_strlen(s2);

  char *str = malloc(s1_len + s2_len + 1);

  if (!str)
    return (NULL);

  ft_strlcpy(str, s1, s1_len + 1);
  ft_strlcat(str, s2, s1_len + s2_len + 1);

  return (str);
}

char *ft_strdup(char *s) {
  char *dup = malloc(ft_strlen(s) + 1);
  int i = 0;

  while (s[i] != '\0') {
    dup[i] = s[i];
    i++;
  }

  dup[i] = '\0';
  return dup;
}
