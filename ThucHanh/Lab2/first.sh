# !/bin/ sh 
# first.sh 
# Script này sẽ tìm trong thư mục hiện hành các chuỗi mang nội dung 
# main( ), nội dung của fìle sẽ được hiển thị ra màn hình nếu tìm thấy. 
for file in * 
do 
if grep -l 'main( ) ' $file 
then 
more $file 
fi 
done 
exit 0