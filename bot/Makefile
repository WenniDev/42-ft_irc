#PROJECT
PROJDIR		=	$(realpath $(CURDIR))
NAME		=	../miniBot
INCDIR		=	$(PROJDIR)/incs
SRCDIR		=	$(PROJDIR)/srcs
OBJDIR		=	$(PROJDIR)/objs
DEPDIR		=	$(PROJDIR)/deps

#COMPILER
CC			=	c++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98
HDINC		=	-I $(INCDIR)
TCPIPv4		=	../TCP_IPv4.lib/TCP_IPv4.a

LIBINC		+=	$(TCPIPv4)

#FILES
INCS		=	-I $(INCDIR)

SRCS		=	$(shell find $(SRCDIR) -type f -name '*'.cpp)

OBJS		=	$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.cpp=.o))
DEPS		=	$(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SRCS:.cpp=.d))

#RULES
all : $(NAME)

$(NAME) : $(OBJS)
	@printf "Linking $@...\n"
	@$(CC) $(CFLAGS) $(HDINC) $(OBJS) -o $@ $(LIBINC)
	@printf "All done\n"

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(dir $(@:.o=.d)))
	@printf "Buildind $(notdir $<)...\n"
	@$(CC) $(CFLAGS) $(HDINC) -c $< -o $@ \
		-MMD -MF $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(@:.o=.d))


-include $(DEPS);	

clean :
	@printf "Cleaning object files...\n"
	@rm -rf $(OBJDIR) $(DEPDIR)

fclean : clean
	@printf "Cleaning target files...\n"
	@rm -rf $(NAME)

re : fclean all

run :
	@echo "Executing ./$(NAME)"
	@./$(NAME)

.PHONY : all clean fclean re