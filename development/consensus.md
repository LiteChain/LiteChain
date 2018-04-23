# This is for solved issue with more improved feature cryptonote
### Method : #[Compiler] - Bugs - Solution
### GCC 4 - More orphan - Removed by reduce dust on CryptonoteConf.h
const uint64_t DEFAULT_DUST_THRESHOLD = UINT64_C(100);
### GCC 4 - Lagging On Daemon - Removed by lag time on CryptonoteConf.h
const size_t DIFFICULTY_LAG = 15; 
### All GCC - failed to handle Notify_Request_Chain - Remove block chain
remove ./[yourcoinname]/blocks.bin and ./[yourcoiname]/blockindexs.bin
### All GCC - Error:tcplistener - Added some command
- ./daemon --allow-local-ip --seed-node 127.0.0.1
### change repo updates
- used git ini since we change updates to cryptonoteevo.git
### json n security issue
Upgrade v2 soon when enable
