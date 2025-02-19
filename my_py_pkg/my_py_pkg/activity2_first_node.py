#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from example_interfaces.msg import Int64

class FirstNode(Node):
    def __init__(self):
        super().__init__("first_node")

        self.topic_name = "number"
        self.num = 2

        self.publisher_ = self.create_publisher(Int64, self.topic_name, 10)
        self.timer_ = self.create_timer(1, self.publish_number)
        self.get_logger().info("First Node has been started!")

    def publish_number(self):
        msg = Int64()
        msg.data = self.num
        self.publisher_.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = FirstNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()