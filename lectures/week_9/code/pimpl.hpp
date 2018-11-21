#include <memory>
#include <string>

class Widget
{
public:
    Widget();

    void setId(std::string const& id);
    void id() const;

private:
    struct WidgetImpl;
    std::unique_ptr<WidgetImpl> mImpl;
};
