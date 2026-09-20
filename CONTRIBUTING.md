# Contributing & Engineering Methodology

## 1. Core Philosophy: Engineering as Applied Science
At ATOP, we reject ad-hoc hacking and trial-and-error development. Engineering is fundamentally the **scientific method applied to creation**. 

While natural sciences use the scientific method for **Discovery**, engineering uses an isomorphic application of the exact same logical rigor for **Creation**. **Any attempt to bypass, subvert, or break the scientific method within this project will be indefinitely vetoed.** We operate under both formal expressions of the scientific method:

### A. The Scientific Method of Discovery (Understanding Reality)
1. **Observation**: Identifying a physical or operational phenomenon.
2. **Hypothesis**: Proposing a model or explanation for the phenomenon.
3. **Experiment Design**: Setting up controlled conditions to test the model.
4. **Experimentation**: Execution and data gathering.
5. **Data Consistency Verification**: Ensuring experimental data is sound and repeatable.
6. **Hypothesis Validation**: Confirming or refuting the proposed model.
7. **Natural Law / Theory**: Establishing reliable principles.

### B. The Scientific Method of Creation (Engineering & Synthesis)
1. **Requirements (Hypothesis of Need)**: Defining what problem needs to be solved and what functional constraints must be met (e.g., Phase 0/A MDD & URD).
2. **Behavioral Design**: Architecting how the system will behave to satisfy the requirements without violating physical or logical boundaries (SRS & Architecture).
3. **Implementation/Manufacturing Procedure**: Formulating the rigorous, reproducible steps required to build the artifact (coding standards, MISRA-C, Power of 10, build pipelines).
4. **Implementation / Execution**: Fabricating or coding the artifact according to the procedure.
5. **Procedure Conformance**: Confirming that the artifact was built *exactly* as specified by the procedure (static analysis, unit testing).
6. **Behavioral Verification**: Proving that the artifact's actual behavior matches the original requirements (via SITL and HITL testing).
7. **Prototype / Product Validation**: Deploying the verified artifact into its operational plant environment (such as UAV flight validation).

---

## 2. Standards as Guardrails
While the scientific method provides the underlying logic, industrial and aerospace standards (**ECSS**, **MISRA-C**, **NASA Power of 10**) serve as our operational guardrails. They exist to eliminate ambiguity, enforce determinism, and prevent systemic errors before code ever touches silicon.

---

## 3. Repository Workflow Procedure
To maintain the integrity of this methodology, all contributions and changes must follow a rigorous lifecycle mirroring the scientific method of creation:

```mermaid
graph TD
    classDef req fill:#d4edda,stroke:#28a745,stroke-width:2px,color:#155724;
    classDef des fill:#cce5ff,stroke:#004085,stroke-width:2px,color:#004085;
    classDef imp fill:#fff3cd,stroke:#ffc107,stroke-width:2px,color:#856404;
    classDef vv fill:#f8d7da,stroke:#dc3545,stroke-width:2px,color:#721c24;
    classDef core fill:#e2e3e5,stroke:#383d41,stroke-width:2px,color:#383d41;

    A([Observe a Need]):::core --> B{Is it necessary for the project?}:::core
    B -->|No| C[Do nothing]:::core
    B -->|Yes| W[Create Main Issue]:::core

    W --> D[Create Requirements Issue]:::req
    D --> E[Open Requirements Branch]:::req
    E --> F[Define Formal Requirements]:::req
    F --> G[Merge PR & Close Requirements Issue]:::req

    G --> H[Create Design Issue]:::des
    H --> I[Open Design Branch]:::des
    I --> J[System Design]:::des
    J --> K[Merge PR & Close Design Issue]:::des

    K --> L[Create Implementation Issue]:::imp
    L --> M[Open Implementation Branch]:::imp
    M --> N[Define Implementation Procedure & Code Implementation]:::imp
    N --> O[Tests and Static Analysis]:::imp
    O --> P{Does implementation comply with procedure?}:::imp
    P -->|No| N
    P -->|Yes| Q[Merge PR & Close Implementation Issue]:::imp

    Q --> RI[Create Integration Issue]:::vv
    RI --> SI[Open Integration Branch]:::vv
    SI --> TI[Integration & Integration Testing]:::vv
    TI --> UI{Do integrated modules satisfy detailed design interfaces?}:::vv
    UI -->|No - Interface Flaw| XI[Merge PR & Close Integration Issue & Reopen Implementation Issue]:::vv
    XI --> M
    UI -->|Yes - Pass| YI[Merge PR & Close Integration Issue]:::vv

    YI --> R[Create Verification Issue]:::vv
    R --> S[Open Verification Branch]:::vv
    S --> T[SIL, HIL]:::vv
    T --> U{Does design satisfy requirements?}:::vv
    U -->|No - Design Flaw| X[Merge PR & Close Verification Issue & Reopen Design Issue]:::vv
    X --> I
    U -->|Yes - Pass| Y[Merge PR & Close Verification Issue]:::vv

    Y --> Z[Create Validation Issue]:::vv
    Z --> AA[Open Validation Branch]:::vv
    AA --> AB[System Validation]:::vv
    AB --> AC{Does it solve the problem?}:::vv
    AC -->|No - Requirement Flaw| AD[Merge PR & Close Validation Issue & Reopen Requirements Issue]:::vv
    AD --> E
    AC -->|Yes - Pass| AE[Merge PR & Close Validation Issue]:::vv
    AE --> AF([Close Main Issue]):::core
```

1. **Issue Tracking**:
   - No change, refactoring, or feature is implemented without a prior formal Issue detailing its rationale and traceability. Branches must explicitly tell their nature (req/..., design/..., feat/..., verify/...).
   - On verification/validation/integration failure, the corresponding upstream Issue is reopened rather than creating a new one, preserving discussion history and traceability.
2. **Documentation-Driven Engineering**:
   - Requirements and design specifications must be updated *before* code implementation.
   - Traceability links must be maintained between requirements and verification artifacts.
4. **Code Quality Gates**:
   - Zero dynamic memory allocation (`malloc` / `heap` usage is strictly prohibited).
   - Full compliance with static analysis rules and coding guidelines.
   - Verification through reproducible testing procedures.
   - **Mandatory Binary Formal Audit**: Every example or reference implementation provided in the repository must undergo and pass a formal binary audit, including static analysis and predictability verification on the target compiled output.
5. **Review & Merge**:
   - No PR can merge into main branch without explicit approval of the system architect, CI/CD validation and required documental traces.
   - Every Pull Request for Implementation, Integration, Verification, or Validation must include the corresponding execution logs, test reports, or traceability matrices as mandatory artifacts before review and merge.
