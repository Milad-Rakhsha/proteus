#ifndef TRANSPORTCOEFFICIENTS_H
#define TRANSPORTCOEFFICIENTS_H
void linearADR_ConstantCoefficientsEvaluate(const int nPoints,
                                            const int nSpace,
                                            const double M,
                                            const double *A,
                                            const double *B,
                                            const double C,
                                            const double t,
                                            const double *x,
                                            const double *u,
                                            double *m,
                                            double *dm,
                                            double *f,
                                            double *df,
                                            double *a,
                                            double *da,
                                            double *phi,
                                            double *dphi,
                                            double *r,
                                            double *dr);
void nonlinearADR_pqrstEvaluate(const int nPoints,
                                const int nSpace,
                                const double M,
                                const double* A,
                                const double* B,
                                const double C,
                                const double p_pow,
                                const double q_pow,
                                const double r_pow,
                                const double s_pow,
                                const double t_pow,
                                const double t,
                                const double *x,
                                const double *u,
                                double *m,
                                double *dm,
                                double *f,
                                double *df,
                                double *a,
                                double *da,
                                double *phi,
                                double *dphi,
                                double *r,
                                double *dr);
void nonlinearADR_pqrstDualEvaluate(const int nPoints,
                                    const int nSpace,
                                    const double M,
                                    const double* A,
                                    const double* B,
                                    const double C,
                                    const double p1,
                                    const double q1,
                                    const double r1,
                                    const double s1,
                                    const double t1,
                                    const double p2,
                                    const double q2,
                                    const double r2,
                                    const double s2,
                                    const double t2,
                                    const double t,
                                    const double *x,
                                    const double *u,
                                    double *m,
                                    double *dm,
                                    double *f,
                                    double *df,
                                    double *a,
                                    double *da,
                                    double *phi,
                                    double *dphi,
                                    double *r,
                                    double *dr);
void unitSquareRotationEvaluate(const int nPoints,
                                const int nSpace,
                                const double *x,
                                const double *u,
                                double *m,
                                double *dm,
                                double *f,
                                double *df);
void twophasePotentialFlowEvaluate(int nPoints,
                                   int nSpace,
                                   double *M,
                                   double *A,
                                   double *B,
                                   double *Bcon,
                                   double *C,
                                   double t,
                                   double *x,
                                   double *u,
                                   double *m,
                                   double *dm,
                                   double *f,
                                   double *df,
                                   double *a,
                                   double *da,
                                   double *phi,
                                   double *dphi,
                                   double *r,
                                   double *dr);
void rotatingPulseVelEvaluate(const int nPoints,
                              const int nSpace,
                              const double self_a,
                              const double *x,
                              const double *u,
                              double *m,
                              double *dm,
                              double *f,
                              double *df,
                              double *a,
                              double *da,
                              double *phi,
                              double *dphi);
void disRotatingPulseVelEvaluate(const int nPoints,
                                 const int nSpace,
                                 const double self_a,
                                 const double *x,
                                 const double *u,
                                 double *m,
                                 double *dm,
                                 double *f,
                                 double *df,
                                 double *a,
                                 double *da,
                                 double *phi,
                                 double *dphi);
void disVelEvaluate(const int nPoints,
                    const int nSpace,
                    const double self_a,
                    const double *x,
                    const double *u,
                    double *m,
                    double *dm,
                    double *f,
                    double *df,
                    double *a,
                    double *da,
                    double *phi,
                    double *dphi);
void burgersDiagonalVelEvaluate(const int nPoints,
                                const int nSpace,
                                const double self_a,
                                const double *u,
                                double *m,
                                double *dm,
                                double *f,
                                double *df,
                                double *a,
                                double *da,
                                double *phi,
                                double *dphi);
void twophasePotentialFlowUpdateFreeSurface(int nPoints,
                                            int nSpace,
                                            double eps,
                                            double* u_levelSet,
                                            double M1, double M2, double *M,
                                            double* A1, double* A2, double *A,
                                            double* B1, double* B2, double *B,
                                            double* Bcon1, double* Bcon2, double *Bcon,
                                            double C1, double C2, double *C);
void twophaseLevelSetCoefficientsUpdateVelocity(int nPoints,
                                                int nSpace,
                                                double v_scale,
                                                double* vIn,
                                                double* vOut);
void twophaseLevelSetCoefficientsEvaluate(int nPoints,
                                          int nSpace,
                                          double* B,
                                          double  t,
                                          double* x,
                                          double* u,
                                          double* grad_u,
                                          double* m, double* dm,
                                          double* h, double* dh,
                                          double* rh);
void twophaseLevelSetCoefficientsEvaluateCI(int nPoints,
                                            int nSpace,
                                            double* B,
                                            double  t,
                                            double* x,
                                            double* u,
                                            double* m, double* dm,
                                            double* f, double* df,
                                            double* a, double* da,
                                            double* phi, double* dphi,
                                            double* r, double* dr);
void twophaseSignedDistanceCoefficientsUpdateSignFunction(int nPoints,
                                                          double smearingFactor,
                                                          double* u,
                                                          double* S);
void twophaseSignedDistanceCoefficientsEvaluate(int nPoints,
                                                int nSpace,
                                                double* S,
                                                double* u,
                                                double* grad_u,
                                                double* m, double* dm,
                                                double* h, double* dh,
                                                double* rh);
void conservativeHeadRichardsMualemVanGenuchtenHomEvaluate(const int nPoints,
                                                           const int nSpace,
                                                           const double rho,
                                                           const double* gravity,
                                                           const double alpha,
                                                           const double n,
                                                           const double m,
                                                           const double thetaR,
                                                           const double thetaSR,
                                                           const double KWs,
                                                           double *u,
                                                           double *mass,
                                                           double *dmass,
                                                           double *f,
                                                           double *df,
                                                           double *a,
                                                           double *da);
#endif
