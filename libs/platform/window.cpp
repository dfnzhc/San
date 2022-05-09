//
// Created by 秋鱼 on 2022/5/9.
//

#include "window.hpp"

#include <utility>

namespace Yuan {

Window::Window(Window::Properties properties)
    : properties_{std::move(properties)}
{

}

Window::Extent Window::resize(const Window::Extent& extent)
{
    if (properties_.resizable)
	{
		properties_.extent.width  = extent.width;
		properties_.extent.height = extent.height;
	}

	return properties_.extent;
}

} // namespace Yuan