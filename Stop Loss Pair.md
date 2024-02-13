


# 4.1 (Stop Loss Pair)


### Idea of strategy

So,the idea of strategy 4.1 is that first we calculate the z-score and then if the z-score obtained is greater than a given threshold we sell the spread expecting that the spread will come down and then we will make profit by buying it similar idea is when the z_score falls below the threshold.
Now the thing is when we bought a spread we expected it to go down but if the position does not behave accordingly its z_score rather than going down goes even further up crossing a given limit we close the position as the position is not behaving as per our expectation and same goes for the other case.
 

### Implementation
Now in this we have maintained the stocks currently in position with the mean and standard deviation of the day when that particular position was initiated and then on each trading day we first go by the strategy if the strategy generates a sell signal we look if we have stock in our position which needs to be sold and if there is any, we sell the one which was bought earliest and if there is no stock and our position allows we start a new position. The case of buy signal is handled similarily.
After applying the strategy we check among all our bought positions if there is any stock whose z-score is behaving unexpectedly and based on the stop_loss_threshold we close the position if required similarly we check among all out sold positions if there is some position which needs to be closed based on the z-score and stop_loss_threshold.


### Corner case
In this one thing can happen on a given trading day the z-score of a stock may cross both the stop_loss_threshold and the threshold so in such a case the strategy will ask to generate a sell signal and if we have no bought positions and the position limit allows we will create a new sell position but this newly opened position may get closed in the check after the strategy where we look for the stocks whose z_score does not satisfy the stop_loss_threshold but in our implementation we have ensured that a postion started today is not closed on the same day.The intuition for the same is that if the z_score of spread is way too different today it is more likely to come near mean in the following days hence closing the position on the same day on account of the z_score not in the stop_loss_threshold limit is not reasonable and hence we decided to not close a position started on same day.