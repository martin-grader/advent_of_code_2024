
.PHONY: test

test:
	bazel test --test_output=errors //...
