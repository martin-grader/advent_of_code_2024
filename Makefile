
.PHONY: test
.PHONY: compile_commands

test:
	bazel test --test_output=errors //...

compile_commands:
	bazel run //:refresh_compile_commands
