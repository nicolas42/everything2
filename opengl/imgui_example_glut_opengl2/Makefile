
IMGUI_DIR = /Users/nick/everything/imgui
CFLAGS = -Wfatal-errors -g -Wall -Wformat -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I/usr/local/include -I/opt/local/include
LFLAGS = -framework OpenGL -framework GLUT -L/usr/local/lib -L/opt/local/lib
all:
	g++ $(CFLAGS) $(LFLAGS) main.cpp $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp $(IMGUI_DIR)/backends/imgui_impl_glut.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl2.cpp 





