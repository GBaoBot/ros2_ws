#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/int64.hpp>

class FirstNode : public rclcpp::Node
{
public:
    FirstNode() : Node("first_node")
    {
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&FirstNode::publish_number, this)); 

        RCLCPP_INFO(this->get_logger(), "First Node has been started!");
    }

private:
    int64_t num = 2;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

    void publish_number()
    {
        auto msg = example_interfaces::msg::Int64();
        msg.data = num;
        publisher_->publish(msg);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<FirstNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}