# Contributing to Madagascar

Thank you for your interest in contributing to **Madagascar**!  
This project is developed and maintained by a global community of researchers and developers who share the goal of advancing **open-source reproducible computational experiments** in geophysics and beyond.

We welcome contributions of all kinds: new code, bug fixes, documentation improvements, testing, and community support.

---

## How to Contribute

### 1. Reporting Issues
- Use the [GitHub Issues](https://github.com/ahay/src/issues) page to report bugs, request features, or suggest improvements.
- Before filing a new issue, please check if it already exists.
- When reporting a bug, include:
  - A clear description of the problem
  - Steps to reproduce
  - Expected vs. actual behavior
  - System/environment details (OS, compiler, Python version, etc.)

### 2. Submitting Changes
- Fork the repository and create your branch from `master`:
  ```bash
  git checkout -b my-feature
  ```
- Follow coding style and conventions (see below).
- Add tests if you’re fixing a bug or adding functionality.
- Update documentation if your change affects usage or workflows.
- Commit messages should be concise and descriptive.
- Open a Pull Request (PR) to the `master` branch.

### 3. Coding Guidelines
- **Languages:** Madagascar is primarily written in C, C++, Fortran, Python, and SCons build scripts.
- **Style:**
  - Use clear, consistent variable and function names.
  - Write modular, maintainable code with inline comments where needed.
  - Keep code formatting consistent with the existing files.
- **Testing:**
  - Run existing test suites before submitting changes.
  - Ensure your code builds and runs on Linux/macOS.

### 4. Documentation
- Document new functions, parameters, and workflows.
- Use clear explanations and examples.
- For reproducible research scripts, include references and data details where appropriate.
- Jupyter notebook examples are also acceptable (see examples at [https://github.com/ahay/src/blob/master/book/tccs/lowrank/lowrank.ipynb](https://github.com/ahay/src/blob/master/book/tccs/lowrank/lowrank.ipynb)

---

## Development Workflow

1. Fork and clone the repo.
2. Create a feature branch.
3. Make changes, keeping them focused and atomic.
4. Test your changes thoroughly.
5. Push to your fork and open a PR.

---

## Community Guidelines
- Be respectful and inclusive.
- Help new contributors learn.
- Discussions should remain constructive and research-focused.
- We follow the principles of **open, reproducible science**.

---

## Need Help?
- Visit the [Madagascar website](https://ahay.org) and [Development blog](https://ahay.org/blog/) for documentation, tutorials, and community resources.
- Use the [mailing list](https://lists.sourceforge.net/lists/listinfo/rsf-devel) for discussions and support.
- Open an [issue](https://github.com/ahay/src/issues) if you encounter a bug.

---

## License
By contributing, you agree that your contributions will be licensed under the same open-source license as Madagascar.
