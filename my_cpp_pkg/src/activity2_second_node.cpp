#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/int64.hpp>

class SecondNode : public rclcpp::Node
{
public:
    SecondNode() : Node("second_node")
    {
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);
        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>("number", 10, std::bind(&SecondNode::callback_number, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "Second Node has been started!");
    }

private:
    int64_t count = 0;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;

    void callback_number(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        count += msg->data;
        auto msg_pub = example_interfaces::msg::Int64();
        msg_pub.data = count;

        publisher_->publish(msg_pub);
    }
    
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SecondNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}