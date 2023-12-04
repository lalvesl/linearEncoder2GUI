# Development Anotations
## List of states on raspberry pi IOs:

| GPIO  | state |            obs             |
| :---: | :---: | :------------------------: |
|   0   | true  |          pull_up           |
|   1   | true  |          pull_up           |
|   2   | true  |          pull_up           |
|   3   | false | pull_up + phisical changed |
|   4   | true  |          pull_up           |
|   5   | true  |          pull_up           |
|   6   | true  |          pull_up           |
|   7   | true  |          pull_up           |
|   8   | true  |          pull_up           |
|   9   | false |
|  10   | false |
|  11   | false |
|  12   | false |
|  13   | false |
|  14   | false |
|  15   | true  | pull_up + phisical changed |
|  16   | false |
|  17   | false |
|  18   | false |
|  19   | false |
|  20   | false |
|  21   | false |
|  22   | false |
|  23   | false |
|  24   | false |
|  25   | false |
|  26   | false |
|  27   | false |

## References
 - [elinux for direct register access](https://elinux.org/RPi_GPIO_Code_Samples#:~:text=different%20C%2DLanguages.-,Direct%20register%20access,-Gert%20van%20Loo);
 - [codeandfile for  beachmarks](https://codeandlife.com/2012/07/03/benchmarking-raspberry-pi-gpio-speed/#:~:text=wave%20is%20generated%3A-,C%3A%20Maximum%20performance,-The%20Raspberry%20Pi);
