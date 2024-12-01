
Solve:

1. exiftool audio
```
 exiftool spell.wav
ExifTool Version Number         : 12.40
File Name                       : spell.wav
Directory                       : .
File Size                       : 11 MiB
File Modification Date/Time     : 2024:11:19 19:27:23+01:00
File Access Date/Time           : 2024:11:19 19:30:15+01:00
File Inode Change Date/Time     : 2024:11:19 19:30:00+01:00
File Permissions                : -rwxrwxrwx
File Type                       : WAV
File Type Extension             : wav
MIME Type                       : audio/x-wav
Encoding                        : Microsoft PCM
Num Channels                    : 1
Sample Rate                     : 48000
Avg Bytes Per Sec               : 96000
Bits Per Sample                 : 16
Product                         : we love casting spells
Date Created                    : 1337
Software                        : wand (libsndfile-1.0.31)
Track Number                    : 14230MHz
ID3 Size                        : 267
Artist                          : pegielm B) & dr. sponge
Title                           : Shadow wizard money gang
Album                           : we love casting spells
Track                           : 14230MHz
Warning                         : [minor] Frame 'TDRC' is not valid for this ID3 version
Recording Time                  : 1337
Genre                           : captured at 14.230MHz
Comment                         : captured at 14.230MHz
User Defined Text               : (Warning) fire spell
Duration                        : 0:01:58
```

Genre,Comment,Track -> Google '14.230MHz' -> SSTV

2. use qsstv to decode the image

3. image contains a discord invite link: discord.gg/dxb2rag4

4. join the discord, use discord api to get hidden channels (REDACTED = discord Authorization token)


```
curl -X GET "https://discord.com/api/v9/guilds/1308319769929318400/channels" -H "Authorization: REDACTED"
```

```
curl -X GET "https://discord.com/api/v9/guilds/1308319769929318400/channels" -H "Authorization: REDACTED"
[{"id":"1308319770503811134","type":0,"last_message_id":"1308474233688555565","flags":0,"guild_id":"1308319769929318400","name":"casual_chat_for_wizards","parent_id":null,"rate_limit_per_user":0,"topic":null,"position":0,"permission_overwrites":[{"id":"1308319769929318400","type":0,"allow":"0","deny":"377957124097"}],"nsfw":false,"icon_emoji":{"id":null,"name":"\ud83d\udc4b"},"theme_color":null},{"id":"1308321009438556261","type":0,"last_message_id":"1308474084828516412","flags":0,"guild_id":"1308319769929318400","name":"very_secret_chat_for_shadow_wizards","parent_id":null,"rate_limit_per_user":0,"topic":"zeroday{now_you_c4n_join_5hadow_wizard_gang}","position":1,"permission_overwrites":[{"id":"1308319769929318400","type":0,"allow":"0","deny":"1024"},{"id":"1308320133437067334","type":0,"allow":"1024","deny":"0"}],"nsfw":false}]
```

5. topic of 'very_secret_chat_for_shadow_wizards' -> flag: 
```
zeroday{now_you_c4n_join_5hadow_wizard_gang}
```