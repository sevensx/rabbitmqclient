// MIT License
//
// Copyright (c) 2021 Yuming Meng
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// @File    :  rabbitmq_receiver.cc
// @Version :  1.0
// @Time    :  2021/09/16 11:35:44
// @Author  :  Meng Yuming
// @Contact :  mengyuming@hotmail.com
// @Desc    :  None

#include <thread>

#include "rabbitmq_client/rabbitmq_client.h"


namespace {

using rabbitmqclient::RabbitmqClient;

} // namespace

int main(void) {
  RabbitmqClient rabbitmq_client;
  rabbitmq_client.InitParameter(
      "amqp://guest:guest@localhost/", "exchange", "queue", "routekey");
  // rabbitmq_client.InitParameter(
  //     "amqps://guest:guest@localhost/", "exchange", "queue", "routekey");
  rabbitmq_client.ConsumerRun();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::vector<char> msg;
  while (rabbitmq_client.service_is_running()) {
    if (rabbitmq_client.get_message(&msg) == 0) {
      printf("Recv[%lu]: %s\n", msg.size(), msg.data());
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }
  rabbitmq_client.ConsumerStop();
  return 0;
}