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
  ros::init (argc, argv, "melfa_driver");
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
  int size = sendto (fd, (char *) &bytes, sizeof (bytes), 0, (struct sockaddr *) &addr, sizeof (addr));

  return 0;
}
