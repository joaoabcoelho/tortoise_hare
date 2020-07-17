# tortoise_hare

This is my solution to the FiveThirtyEight Riddler classic puzzle of 17/07/2020: https://fivethirtyeight.com/features/can-the-hare-beat-the-tortoise/

The problem states the road is magic and stretches every minute to become 10 miles longer. If we redefine the units every time this happens, we can instead think of the road as having a fixed length of 10 units, but the speed of the cars is reduced by a factor 1/n at the beginnning of the n-th minute. If we start at t=0, as the tortoise does, she will cover a distance sum(1/k for k from 1 to n) = H_n in n minutes, where H_n is the n-th harmonic number. The total time for the tortoise is then given by the largest n such that H_n < 10, which is given by n=12366, plus a small correction (10-H_n)*(n+1) ~ 0.468 to reach the finish line.

For the hare, we have an initial waiting period of w minutes. Defining k0 = ceil(w), we have the distance covered being (k0-w)*v/k0 + (H_n - H_k0)*v + (10-H_n)*v. The first term is a small distance covered before the first change in speed. The middle term is a harmonic sum between k0 and n. And the final term is the last small distance covered before the finish line. We want to find w such that this distance is equal to 10 units. This can be done numerically.

Here I took a more direct approach of simulating the race as described in the puzzle and finding the required waiting time for any hare speed v using Newton's method. 

At 75 mph, the hare needs to wait 3m 40s before starting in order to finish at the same time as the tortoise. They will both cross the finish line in 8d 14h 6m 28.09s!

Here's how the waiting time depends on the speed of the hare:

!["Hare waiting time vs speed"](waittime_vs_speed.png)

And in the 75 mph solution, the magical stretching makes the tortoise distance to the hare increase for 3.2 days until finally the hare starts to catch up. At the peak, the distance between them reaches 1138 miles!

!["Tortoise-Hare distance vs time"](distance_vs_time.png)
