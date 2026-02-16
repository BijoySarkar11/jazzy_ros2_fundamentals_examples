#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1; // for binding the callback function

class MinimalCppSubscriber : public rclcpp::Node
{
    public:
        MinimalCppSubscriber(): Node("minimal_cpp_subscriber")
        {
            subscriber_ = create_subscription<std_msgs::msg::String>(
                "/cpp_example_topic", 10, std::bind(&MinimalCppSubscriber::topic_callback, this, _1));
            RCLCPP_INFO(get_logger(), "Subscribed to /cpp_example_topic");
        }

    
        void topic_callback(const std_msgs::msg::String & msg) const
        {
            RCLCPP_INFO_STREAM(get_logger(), "I heard: " << msg.data.c_str());
        }
        private:
            rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;

};
int main(int argc, char *argv[])
{
    rclcpp::init(argc,argv);
    auto minimal_cpp_subscriber_node = std::make_shared<MinimalCppSubscriber>();
    rclcpp::spin(minimal_cpp_subscriber_node);
    rclcpp::shutdown();
    return 0;
}