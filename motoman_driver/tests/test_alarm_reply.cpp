#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <ros/ros.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <boost/algorithm/hex.hpp>

int main (int argc, char **argv){
  ros::init (argc, argv, "test_alarm_reply");
  ros::NodeHandle nh;

  std::string robot_ip = "10.36.85.192";
  int fd = socket (AF_INET, SOCK_DGRAM, 0);
  if (fd < 0) {
    ROS_ERROR ("Cannot open socket");
    exit(1);
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons (10040);
  addr.sin_addr.s_addr = inet_addr (robot_ip.c_str());

  // 31 byte package info from Ted Miller: to request alarm data
  std::string req = "59455243200000000301000000000000393939393939397000010000010000";
  char bytes[31] = {0};
  std::string hash = boost::algorithm::unhex(req);
  std::copy(hash.begin(), hash.end(), bytes);
  std::cout << "  > Sending packet data to controller\n";
  int size = sendto (fd, (char *) &bytes, sizeof (bytes), 0, (struct sockaddr *) &addr, sizeof (addr));
  if (size != sizeof (bytes)) {
    ROS_ERROR ("Connot send packet controller.");
    exit (1);
  }
  std::cout << "  > Successfully sent!\n";

  ros::Duration(1.0).sleep();



  std::cout << "  > Attempting to receive packet data\n";

  fd_set fds;
  timeval time;

  FD_ZERO (&fds);
  FD_SET (fd, &fds);

  time.tv_sec = 0;
  time.tv_usec = 2 * 0.5 * 1000000;
  //
  // int status = select (fd+1, &fds, (fd_set *) NULL, (fd_set *) NULL, &time);
  // if (status < 0) { ROS_ERROR ("Cannot receive packet"); }
  //
  char results[100] = {0};
  // if ((status > 0) && FD_ISSET (fd, &fds)) {
    size = recvfrom(fd, &results, sizeof (results), 0, NULL, NULL);
    if (size < 0) {
      ROS_ERROR ("recvfrom failed");
      exit (1);
    }
  // }
  // else {
  //   exit(1);
  // }
  std::cout << "  > Successfully received!\n";

  for (int i = 0; i < 100; i++){
    std::cout << results[i] << "\n";
  }

  char result_bytes[33];
  for (int i = 28; i < 60; i++){
    result_bytes[i-28] = results[i];
  }

  // Print out the reply for debugging
  std::string s(results, sizeof(results));
  std::cout << s << "\n";

  std::string s2(result_bytes, sizeof(result_bytes));
  std::cout << s2 << "\n";
  return 0;
}
