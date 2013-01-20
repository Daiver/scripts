
def twiddle(estimate, p, tol = 0.2): #Make this tolerance bigger if you are timing out!
############## ADD CODE BE:LOW ####################
            


    # -------------
    # Add code here
    # -------------
    #dp = [1, 1, 1]
    dp = [1 for i in xrange(len(p))]
    besterror = estimate(p)
    while besterror > 0.00000001:
        for i in xrange(len(p)):
            p[i] += dp[i]
            error = estimate(p)
            if error < besterror:
                dp[i] *= 1.1
                besterror = error
            else:
                p[i] -= 2*dp[i]
                error = estimate(p)
                if error < besterror:
                    dp[i] *= 1.1
                    besterror = error
                else:
                    p[i] += dp[i]
                    dp[i] *= 0.9
    return estimate(p)


if __name__ == '__main__':
    p = [0, 0, 0]
    def est(p):
       f = lambda p:p[0] * 2 + p[1] * 3 + p[2] * 1
       res = f(p)
       return abs(res - 7)

    print twiddle(est, p)
    print p
