# minishell

minishell is a 42 school team project where we have to write a little shell. Our program must be able to pars a prompt and to launch executables with arguments along with a few built-in functions.

## Status

* Success
* Grade: 99/100

## Rules

Our shell should:
* Show a **prompt** when waiting for a new command.
* Have a functional **history**.
* Search and launch the right executable (based on the PATH variable or by using relative or absolute path).
* Do not interpret unclosed _quotes_ **'** **"** or special characters not requested in the subject such as **\\** or **;**.
* **'** (_single quote_) should prevent the shell from interpreting meta-characters present in the sequence between quotes.
* **"** (_double quote_) should prevent the shell from interpreting meta-characters present in the sequence between quotes except **$**.
* **<** should redirect the input.
* **>** should redirect the output.
* **<<** should receive a delimiter and read the input until it contains a line with the delimiter. However, the history does not need to be updated.
* **>>** should redirect output in _append_ mode.
* Implement **pipes ( | )**: The output of each command in the _pipeline_ is connected to the input of the next command using a _pipe_.
* Manage **environment variables** (**$** followed by a sequence of characters) which must be substituted by their content.
* **$?** should be substituted by the exit status of the last pipeline executed in the foreground.
* ```ctrl-C```, ```ctrl-D``` and ```ctrl-\``` should work like in bash.

Our shell should implement following **builtins**:
* ```echo``` with ```-n``` option.
* ```cd``` with only using relative or absolute path.
* ```pwd``` without any options.
* ```export``` without any options.
* ```unset``` without any options.
* ```env``` without any options or arguments.
* ```exit``` without any options.

## Project content

This project contains a **libft** folder which is a library that we had to create as the first 42 school project. This folder also includes files corresponding to the following 42 school project: **ft_printf** and **get_next_line**.

## Usage

Use ```make``` command to compile then run it with:
```
./minishell
```
***
Made by:
* Ismérie George: <ismerie.george@gmail.com>
* Thibaut Charpentier: <thibaut.charpentier42@gmail.com>
