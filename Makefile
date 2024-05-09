# Định nghĩa biến
CXX = g++
CXXFLAGS = -Wall -Wextra -g

# Thư mục chứa các tệp nguồn
SRCDIR = src
# Thư mục chứa các tệp tiêu đề
HPPDIR = hpp
# Thư mục chứa các tệp đầu ra (đối tượng và chương trình)
BUILDDIR = obj

# Tệp nguồn
SRCS = $(wildcard $(SRCDIR)/*.cpp)
# Tệp tiêu đề
HDRS = $(wildcard $(HPPDIR)/*.h)

# Tên chương trình đầu ra
TARGET = main.exe

# Thư mục chứa thư viện SDL2.dll
SDL_LIB_DIR = SDL2-devel-2.30.3-mingw/SDL2-2.30.3/i686-w64-mingw32/bin

# Tạo các đường dẫn tệp đối tượng tương ứng
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Phần quy tắc biên dịch các tệp .cpp thành các tệp .o
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I./$(HPPDIR)

# Phần quy tắc liên kết các tệp đối tượng thành chương trình
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -L$(SDL_LIB_DIR) -lSDL2 -lSDL2_mixer -llibmpg123-0

# Quy tắc mặc định sẽ chạy mục tiêu cuối cùng
.DEFAULT_GOAL := $(TARGET)

# Xóa các tệp đối tượng và các tệp đầu ra khi thực hiện "make clean"
clean:
	del $(BUILDDIR) $(TARGET)
