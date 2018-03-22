#ifndef COMMANDS_H_
#define COMMANDS_H_

#define MD_FWD_CMD 0x1;
#define MD_BWD_CMD 0x0;
#define GET_MD_DIR(cmd) (cmd & (1<<7))

#define LDR_WATCH_CMD_ON 0x0;
#define LDR_WATCH_CMD_OFF 0x0;

#endif