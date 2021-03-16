#털과 날개가 있는지 없는지에 따라, 포유류인지 조류인지 분류
import tensorflow as tf   
import numpy as np  #넘파이는 배열
#[털, 날개]
x_data = np.array([[0,0], [1,0], [1,1], [0,0], [0,0], [0,1]])
#[기타, 포유류, 조류]
y_data = np.array([
    [1,0,0], #기타
    [0,1,0], #포유류
    [0,0,1], #조류
    [1,0,0], 
    [1,0,0], 
    [0,0,1]
])
#신경망 모델 구성############
X = tf.placeholder(tf.float32)
Y = tf.placeholder(tf.float32)
# 첫번째 가중치의 차원은 [특성, 히든레이어의 뉴런 갯수] -> [2, 10]
W1 = tf.Variable(tf.random_uniform([2,10], -1.,1.))
# 두번째 가중치의 차원을 [첫번째 히든 레이어의 뉴런 갯수, 분류갯수]
# -> [10,3] 으로 정합니다.
W2 = tf.Variable(tf.random_uniform([10,3], -1.,1.))
#편향을 각각 각 레이어의 아웃풋 갯수로 설정합니다
b1 = tf.Variable(tf.zeros([10]))
b2 = tf.Variable(tf.zeros([3]))
#신경망의 히든 레이어에 가중치 W1과 편향 b1을 적용합니다. 
L1 = tf.add(tf.matmul(X, W1), b1)  # (X*W1) + b1 
L1 = tf.nn.relu(L1)                #활성화 함수를 계산을 한다. 
#최종적인 아웃풋을 계산합니다. 
#3개의출력값생성
model = tf.add(tf.matmul(L1, W2), b2)

cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels = Y, logits=model))  #Y랑 model 사이에 오차를 구해준다

optimizer = tf.train.AdamOptimizer(learning_rate = 0.01)  #이런 종류의 옵티마이저를 쓴다. #사실 여기서 줄여도 되는데, 한번 더 밑에서 해주는 것 같다.
train_op = optimizer.minimize(cost)     #오차를 줄이는 트레인 오퍼레이션

# 신경망모델학습######
#######여기서 부터 계산 시작########
init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)
for step in range(100):
    sess.run(train_op, feed_dict={X: x_data, Y: y_data})
    
    if (step + 1) % 10 == 0:
        print(step + 1, sess.run(cost, feed_dict={X: x_data, Y: y_data}))
# 결과확인########## 
# # 0: 기타1: 포유류, 2: 조류####### 

prediction = tf.argmax(model, 1)
target = tf.argmax(Y, 1)
print('예측값:', sess.run(prediction, feed_dict={X: x_data}))
print('실제값:', sess.run(target, feed_dict={Y: y_data}))

is_correct = tf.equal(prediction, target)
accuracy = tf.reduce_mean(tf.cast(is_correct, tf.float32))
print('정확도: %.2f' % sess.run(accuracy * 100, feed_dict={X: x_data, Y: y_data}))