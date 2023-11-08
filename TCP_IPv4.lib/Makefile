#------------------------------------#
#               Project              #
#------------------------------------#
TARGET		=	TCP_IPv4.a
PROJDIR		=	$(realpath $(CURDIR))
SRCDIR		=	$(PROJDIR)/srcs
INCDIR		=	$(PROJDIR)/incs
OBJDIR		=	$(PROJDIR)/objs
DEPDIR		=	$(PROJDIR)/.deps

#------------------------------------#
#               Compiler             #
#------------------------------------#
CC			=	c++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98
INCLUDE		=	-I $(INCDIR)

#------------------------------------#
#                Files               #
#------------------------------------#
SRCS		=	$(shell find $(SRCDIR) -type f -name '*'.cpp)
OBJS		=	$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.cpp=.o))
DEPS		=	$(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SRCS:.cpp=.d))

#------------------------------------#
#                Rules               #
#------------------------------------#
all : $(TARGET)

$(TARGET) : $(OBJS)
	@ar -src $@ $^
	@echo Linking $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(dir $@))
	@$(CC) $(CFLAGS) $(CUS) $(INCLUDE) -c $< -o $@ -MMD -MF $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(@:.o=.d))
	@echo Building $(notdir $@)

-include $(DEPS)

clean :
	@rm -rf $(OBJDIR)
	@rm -rf $(DEPDIR)
	@echo Cleaning $(OBJDIR) $(DEPDIR)

fclean : clean
	@rm -f $(TARGET)
	@echo Cleaning $(TARGET)

re : fclean all

.PHONY : all clean fclean re