#include "tap.h"
#include "test.h"
#include "mongo-utils.h"

#include <string.h>

void
test_mongo_utils_parse_addr (void)
{
  gchar *host = "deadbeef";
  gint port = 42;

  ok (mongo_util_parse_addr (NULL, &host, &port) == FALSE,
      "mongo_util_parse_addr() fails with a NULL address");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("127.0.0.1:27017", &host, NULL) == FALSE,
      "mongo_util_parse_addr() fails when port is NULL");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("127.0.0.1:27017", NULL, &port) == FALSE,
      "mongo_util_parse_addr() fails when host is NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("127.0.0.1:27017", &host, &port),
      "mongo_util_parse_addr() can parse HOST:PORT pairs");
  is (host, "127.0.0.1",
      "Host parsed successfully");
  cmp_ok (port, "==", 27017,
          "Port parsed successfully");
  g_free (host);
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr (":27017", &host, &port) == FALSE,
      "mongo_util_parse_addr() should fail when no host is specified");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("localhost:27017garbage", &host, &port) == FALSE,
      "mongo_util_parse_addr() should fail if there is garbage after "
      "the port");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("localhost:garbage", &host, &port) == FALSE,
      "mongo_util_parse_addr() should fail if the port is not a number");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("localhost:-10", &host, &port) == FALSE,
      "mongo_util_parse_addr() should fail if the port is out of bounds");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("localhost:9999999999999999999",
                             &host, &port) == FALSE,
      "mongo_util_parse_addr() should fail if the port is out of bounds");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("localhost:9999999999",
                             &host, &port) == FALSE,
      "mongo_util_parse_addr() should fail if the port is out of bounds");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  /* IPv6 */
  ok (mongo_util_parse_addr ("::1:27017", &host, &port),
      "mongo_util_parse_addr() can deal with IPv6 addresses");
  is (host, "::1",
      "Host parsed successfully");
  cmp_ok (port, "==", 27017,
          "Port parsed successfully");
  g_free (host);
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("::1", &host, &port),
      "mongo_util_parse_addr() should silently misparse ambigous "
      "IPv6 addresses");
  isnt (host, "::1",
        "Host is misparsed, as expected");
  cmp_ok (port, "==", 1,
          "Port is misparsed, as expected");
  g_free (host);
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("[::1", &host, &port) == FALSE,
      "mongo_util_parse_addr() should fail on invalid IPv6 literals");
  is (host, NULL,
      "Host should be NULL");
  cmp_ok (port, "==", -1,
          "Port should be -1");
  g_free (host);
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("[::1]:1", &host, &port),
      "mongo_util_parse_addr() works with IPv6 literal + port");
  is (host, "::1",
      "Host should be ::1");
  cmp_ok (port, "==", 1,
          "Port should be 1");
  g_free (host);
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("[::1]:27017", &host, &port),
      "mongo_util_parse_addr() works with IPv6 literal + port");
  is (host, "::1",
      "Host should be ::1");
  cmp_ok (port, "==", 27017,
          "Port should be 27017");
  g_free (host);
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("[]:27017", &host, &port) == FALSE,
      "mongo_util_parse_addr() should fail when no host is specified");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("[::1]:27017garbage", &host, &port) == FALSE,
      "mongo_util_parse_addr() should fail if there is garbage after "
      "the port");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("[::1]:garbage", &host, &port) == FALSE,
      "mongo_util_parse_addr() should fail if the port is not a number");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("[::1]:-10", &host, &port) == FALSE,
      "mongo_util_parse_addr() should fail if the port is out of bounds");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("[::1]:9999999999999999999",
                             &host, &port) == FALSE,
      "mongo_util_parse_addr() should fail if the port is out of bounds");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("[::1]:9999999999",
                             &host, &port) == FALSE,
      "mongo_util_parse_addr() should fail if the port is out of bounds");
  is (host, NULL,
      "Failed parsing sets host to NULL");
  cmp_ok (port, "==", -1,
          "Failed parsing sets port to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("/var/run/mongodb/mongodb.socket",
                             &host, &port) == TRUE,
      "mongo_util_parse_addr() works with unix domain sockets");
  is (host, "/var/run/mongodb/mongodb.socket",
      "Parsing a Unix domain socket sets host to the socket name");
  cmp_ok (port, "==", -1,
          "Port is set to -1");
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("[::1]", &host, &port),
      "mongo_util_parse_addr() can handle IPv6 literals without port set");
  is (host, "::1",
      "Host parsed successfully");
  cmp_ok (port, "==", -1,
          "Port is set to -1");
  g_free (host);
  host = "deadbeef";
  port = 42;

  ok (mongo_util_parse_addr ("/var/run/mongodb/mongodb.socket:-1",
                             &host, &port) == TRUE,
      "mongo_util_parse_addr() can parse unix domain sockets with -1 port");
  is (host, "/var/run/mongodb/mongodb.socket",
      "Parsing a unix domain socket sets host to the socket name");
  cmp_ok (port, "==", -1,
          "Parsing a unix domain socket with a port set to -1, works");
  g_free (host);
  host = "deadbeef";
  port = 42;
}

RUN_TEST (70, mongo_utils_parse_addr);
