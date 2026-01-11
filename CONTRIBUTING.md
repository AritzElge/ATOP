# Contributing to ATOP

Thank you for considering contributing to ATOP. While this is a personal project, feedback, bug reports, and suggestions are welcome.

## How to Contribute

1. **Open an Issue**: Before proposing changes, open an issue to describe the problem or enhancement.
2. **Link to Requirements**: If applicable, reference the relevant requirement (e.g., `Closes FR-01`).
3. **Pull Requests**: Ensure your code:
   - Follows the coding standards (`CODING_STANDARDS.md`).
   - Includes tests if applicable.
   - Updates documentation.
   - Passes CI checks (static analysis, build).

## Development Workflow

- Use `main` as the main branch.
- Name feature/fix branches as `feat/description` or `fix/description`.
- Commit messages should be clear and follow: `type: brief description`.

## Definition of Done (DoD)

All contributions must satisfy the following project-wide requirements:

- [ ] No dynamic memory allocation (`malloc`, `free` prohibited) — complies with **NFR-02**.
- [ ] All function pointers are validated for `NULL` before use — complies with **NFR-03**.
- [ ] No direct access to internal state; encapsulation is enforced — complies with **AR-02**.
- [ ] System parameters and buffer sizes are defined at compile-time — complies with **AR-03**.
- [ ] Hardware interaction occurs only through defined interfaces (HAL/DAL) — complies with **AR-04**.
- [ ] Code adheres to `CODING_STANDARDS.md` (including MISRA C:2012 deviations).
- [ ] All changes pass static analysis and CI checks.
- [ ] Documentation is updated.
- [ ] Pull request links to relevant requirement (e.g., `Closes FR-01`).

## Communication

All technical discussions are managed via issues and pull requests. Direct commits without review are not accepted.

Your collaboration helps improve the system's quality and reliability.   