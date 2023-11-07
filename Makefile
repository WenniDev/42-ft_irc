#------------------------------------#
#               Project              #
#------------------------------------#
TARGET		=	ircserv
PROJDIR		=	$(realpath $(CURDIR))
SRCDIR		=	$(PROJDIR)/srcs
INCDIR		=	$(PROJDIR)/includes
OBJDIR		=	$(PROJDIR)/objs
DEPDIR		=	$(PROJDIR)/.deps
LIBDIR		=	$(PROJDIR)/TCP_IPv4.lib

#------------------------------------#
#               Compiler             #
#------------------------------------#
CC			=	c++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -fsanitize=address
INCLUDE		=	-I $(INCDIR)

#------------------------------------#
#                Files               #
#------------------------------------#
SRCS		=	$(shell find $(SRCDIR) -type f -name '*'.cpp)
OBJS		=	$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.cpp=.o))
DEPS		=	$(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SRCS:.cpp=.d))
LIB			=	$(LIBDIR)/TCP_IPv4.a
LIBDEP		=	$(shell find $(LIBDIR)/srcs -type f -name '*'.cpp)

#------------------------------------#
#                Rules               #
#------------------------------------#
all : $(TARGET)

$(TARGET) : $(LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@ $(LIB)
	@echo Linking $@

$(LIB) : $(LIBDEP)
	@make -C $(LIBDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(dir $@))
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -MMD -MF $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(@:.o=.d))
	@echo Building $(notdir $@)

-include $(DEPS)

clean :
	@rm -rf $(OBJDIR)
	@rm -rf $(DEPDIR)
	@make clean -C $(LIBDIR)
	@echo Cleaning $(OBJDIR) $(DEPDIR)

fclean : clean
	@make fclean -C $(LIBDIR)
	@rm -f $(TARGET)
	@echo Cleaning $(TARGET)

re : fclean all

.PHONY : all clean fclean re