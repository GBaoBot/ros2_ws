#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from example_interfaces.msg import Int64

class SecondNode(Node):
    def __init__(self):
        super().__init__("second_node")

        self.sum = 0

        self.subscriber_ = self.create_subscription(Int64, "number", self.callback_number, 10)
        self.publisher_ = self.create_publisher(Int64, "number_count", 10)
        self.get_logger().info("Second Node has been started!")

    def callback_number(self, msg):
        self.sum += msg.data
        msg_pub = Int64()
        msg_pub.data = self.sum

        self.publisher_.publish(msg_pub)
        # self.get_logger().info(msg.data)


def main(args=None):
    rclpy.init(args=args)
    node = SecondNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()