#define VOLUME_NAME_1 "Gaming"
#define VOLUME_NAME_2 "Chat"
#define VOLUME_NAME_3 "Media"
#define VOLUME_NAME_4 "Headset"
#define VOLUME_NAME_5 "Mic"

#define VOLUME_1_IS_INPUT false
#define VOLUME_2_IS_INPUT false
#define VOLUME_3_IS_INPUT false
#define VOLUME_4_IS_INPUT false
#define VOLUME_5_IS_INPUT true

#define VOLUME_AMOUNT 5 //max is 5, set to the amount of volumes actually initialized
#define PAGE_AMOUNT 6 // amount -1 of how many volumes have their own page, page 0 is a home page that shows the first 4 volumes
// the extra pages start at index 4 and go down to 0 so AMOUNT = 2 means all 4 volumes are only on home page and only volume 5 has its own page