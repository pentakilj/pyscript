### 提取视频中每一帧的图片，
# 设置图片质量 -q:v 0 , 0～2 高～低
# -r 抽取的帧率，每秒抽取的帧数
# 不加-r 默认提前视频的每一帧
ffmpeg -i a.mkv -f image2 test%05d.png

ffmpeg -i a.mkv -vf "select=(gte(t\,120))*(isnan(prev_selected_t)+gte(t-prev_selected_t\,120))"  tile.png
ffmpeg -i a.mkv -vf "select=between(n\,20\,200)" -c copy 2.mp4

ffmpeg -i a.mkv -vf "select=between(n\,20\,200)" -y -c copy a1.mp4
# 每个4秒，提取84-208帧的图片
ffmpeg -i a.mkv -vf "select=between(n\,84\,208)*not(mod(n\,4))" -vsync 0 image_%05d.jpg

# vframes 1 只抽取一帧视频
######### 抽取视频关键帧（I P B 帧）
# 一般60s的视频16个I帧，84个P帧，184个B帧，I帧信息最多
# 提取 IPB帧时间
ffprobe -i 1.mkv -v quiet -select_streams v -show_entries frame=pkt_pts_time,pict_type
# 提取 I帧 (P, B)为图片
ffmpeg -i 1.mkv -vf "select=eq(pict_type\,I)" -vsync vfr -q:v 0 -f image2 test_%05d.jpg

####### 抽取场景转换帧 0.4 为概率
#ffmpeg -i 1.mkv -filter:v "select='gt(scene,0.1)',showinfo" -f null - 2>&1
ffmpeg -i 1.mkv -filter:v "select='gt(scene,0.3)',showinfo" -f image2 test_%05d.jpg

######### 查看视频帧数
# 计算后在查看
# ffprobe -v error -count_frames -select_streams v:0 -show_streams a.mkv |grep nb_read_frames
# 过滤结果
ffprobe -v quiet  -count_frames -select_streams v:0 -show_entries stream=nb_read_frames -of default=nk=1:nw=1 a.mkv
## 说明
# -v quiet ， -v error 不输出版本等信息
# -count_frames 计算流，并报告
# -select_streams v:0 选择视频流
# -show_entries stream=nb_read_frames 之显示读取的帧数
# -of default=nk=1:nw=1 输出格式为默认，不打印键（nokey=1),不打印节头和页脚（noprint_wrappers=1)
##### 按帧提取视频
fmpeg -i a.mkv -vf "select=between(n\,26\,211)" -y -acodec copy a1.mp4

##  截取长度生成gif
ffmpeg -ss 5:40 -t 60 -i 20161123195248.m2ts  -s 480*270 -f gif  test.gif


## 只抽取视频
ffmpeg -i test.avi -c:v copy -an t.avi
## 抽取视频中的音频

ffmpeg -i 1.mkv -vf "select=eq(pict_type\,I)" -vsync vfr -q:v 0 -f image2 test_%05d.jpg
## 提取一段时间的视频文件 -i input -ss start time -to end time
## 没做编码，默认保持视频原有质量
# filter类参数只对最近的输入或输出参数生效，在-i前，则对输入剩下，输出前，则对输出生效
# -ss -to -t 放在输入参数时，能更好的查找时间，减少黑屏（对输出生效时，容易产生黑屏）
# 视频编码（-c:v codec_name)
# 全局覆盖（-y)质量
# 如更准确的查找时间（-accurate_seek)
# 对-c copy参数，加上 -avoid_negative_ts 1 ,才能使用concat demuxer
# 一般提取
ffmpeg -i dafopalda.mp4 -ss 00:19:00 -to 00:21:00 test.mp4
# 优化减少黑屏，保持准确性（推荐，耗时段，质量不错） 有了copy参数单独对c:v,c:a的设置不会生效
ffmpeg -y -ss 22:04 -to 24:09 -accurate_seek -i in.mkv -c copy -avoid_negative_ts 1 t.mkv
# 对音视频分别处理，更耗时间，与提取出来的时间相关
ffmpeg -y -ss 22:04 -to 24:09 -accurate_seek -i in.mkv  -c:v libx264 -c:a copy -avoid_negative_ts 1 t.mkv

## 分割视频
类似
ffmpeg -f concat -safe 0 -i mp4file  out.mp4 -hide_banner


## 合并
# 创建需要合并的视频文件列表 filelist.txt 列表格式 'file file_name'
# 出现unsafe file name 需要在输入参数前 加上 -safe 0
# 尽量使用 -c copy 输出文件
# -hide_baffprobe <input> -select_streams v -show_entries stream=duration -of default=nk=1:nw=1 -v quietnner 隐藏多余显示参数
# 输出文件之前 -qscale 0 保持相同视频质量，
# -intra 帧内编码
ffmpeg -f concat -safe 0 -i filelist  out.mp4 -hide_banner
门票格式

########## 水印
# 查看定位水印位置
ffplay -i al.mp4 -vf delogo=x=306:y=230:w=500:h=100:show=1
# 勉强去水印
ffmpeg -i al.mp4 -vf delogo=x=306:y=230:w=500:h=100 al2.mp4


ffprobe <input> -count_packets -select_streams v -show_entries stream=duration -of default=nk=1:nw=1 -v quiet

ffprobe <input> -select_streams v -show_entries stream=duration -of default=nk=1:nw=1 -v quiet

ffprobe <input> -select_streams v -show_entries stream=duration -of default=nk=1:nw=1 -v quietffprobe <input> -select_streams v -show_entries stream=duration -of default=nk=1:nw=1 -v quiet

ffprobe <input> -select_streams v -show_entries stream=duration -of default=nk=1:nw=1 -v quiet
