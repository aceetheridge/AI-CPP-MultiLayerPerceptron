#!/usr/bin/env python
"""
	The copyright of this code is granted by:
	https://www.kaggle.com/pinocookie/pytorch-simple-mlp

    Code has been modified for Real Time AI course

    How to run the code:
    * Pre-requisite:
        * Download and install Anaconda from here:
        https://www.anaconda.com/distribution/#download-section
        * Run Anaconda prompt from start menu and install pytroch:
        conda install pytorch-cpu torchvision-cpu -c pytorch
    * Run the code in Anoconda prompt:
        python pytorch-simple-mlp.py

"""

import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)
import matplotlib.pyplot as plt

from sklearn.model_selection import train_test_split





import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset, DataLoader

import torchvision
import torchvision.transforms as transforms
from torchvision.utils import make_grid





class MNIST(Dataset):
    def __init__(self, X, y=None, transform=None):
        self.X = X
        self.y = y
        self.transform = transform
        
    def __len__(self):
        return len(self.X.index)
    
    def __getitem__(self, index):
        image = self.X.iloc[index, ].values.astype(np.uint8).reshape((28, 28, 1))
        
        if self.transform is not None:
            image = self.transform(image)
            
        if self.y is not None:
            return image, self.y.iloc[index]
        else:
            return image





train_df = pd.read_csv('./input/train.csv')
test_df = pd.read_csv('./input/test.csv')

print('train data shape : ', train_df.shape)
print('test data shape : ', test_df.shape)





X_train, X_valid, y_train, y_valid =     train_test_split(train_df.iloc[:, 1:], train_df['label'], test_size=1/6, random_state=42)

X_test = test_df

print('train image shape : ', X_train.shape)
print('train label shape : ', y_train.shape)
print('valid image shape : ', X_valid.shape)
print('valid label image : ', y_valid.shape)
print('test image shape  : ', X_test.shape)





transform=transforms.Compose([
    transforms.ToPILImage(),
    transforms.RandomRotation(10),
    transforms.ToTensor()
])

train_dataset = MNIST(X=X_train, y=y_train, transform=transform)
valid_dataset = MNIST(X=X_valid, y=y_valid, transform=transforms.ToTensor())
test_dataset = MNIST(X=X_test, transform=transforms.ToTensor())

train_loader = DataLoader(dataset=train_dataset, batch_size=128, shuffle=True)
valid_loader = DataLoader(dataset=valid_dataset, batch_size=128, shuffle=False)
test_loader = DataLoader(dataset=test_dataset, batch_size=128, shuffle=False)





dataiter = iter(train_loader)
images, labels = dataiter.next()

print('images shape on PyTroch : ', images.size())
print('labels shape on PyTroch : ', labels.size())





grid = make_grid(images[:25], nrow=5)

fig, ax = plt.subplots(figsize=(15, 10))
ax.imshow(grid.numpy().transpose((1, 2, 0)))
ax.axis('off')
plt.show()





class MLP(nn.Module):
    def __init__(self):
        super(MLP, self).__init__()
        '''
        self.layers = nn.Sequential(
            nn.Linear(784, 100),
            nn.ReLU(),
            nn.Linear(100, 10)
        )
        '''
        self.fc_layer0 = nn.Linear(784, 100)
        self.d_l = nn.Dropout(p=0.5) # This layer is only applied during the training phase. Shouldn't be implemented on FPGA.
        self.af_layer1 = nn.ReLU()
        self.fc_layer2 = nn.Linear(100, 10)
        
    def forward(self, input):
        # convert tensor (128, 1, 28, 28) --> (128, 1*28*28)
        
        input_flatten = input.view(input.size(0), -1)
        l0_output = self.fc_layer0(input_flatten)
        l0_output_d = self.d_l(l0_output)
        l1_output = self.af_layer1(l0_output_d)
        l2_output = self.fc_layer2(l1_output)

        #x = self.layers(x)
        return l2_output





model = MLP()

print("Model's state_dict:")
for param_tensor in model.state_dict():
    print(param_tensor, "\t", model.state_dict()[param_tensor].size())




optimizer = torch.optim.Adam(model.parameters(), lr=0.001)
loss_fn = nn.CrossEntropyLoss()





mean_train_losses = []
mean_valid_losses = []
valid_acc_list = []
epochs = 50

for epoch in range(epochs):
    model.train() # Put the network in training mode.
    
    train_losses = []
    valid_losses = []
    for i, (images, labels) in enumerate(train_loader):
        
        optimizer.zero_grad()
        
        outputs = model(images)
        loss = loss_fn(outputs, labels)
        loss.backward() # Calculate the error at the network input (Back-propagation)
        optimizer.step() # Update model netwoks (weights and biases)
        
        train_losses.append(loss.item())
        
        if (i * 128) % (128 * 100) == 0:
            print(f'{i * 128} / 35000')
            
    model.eval() # Put the network in evaluation mode.
    correct = 0
    total = 0
    with torch.no_grad():
        for i, (images, labels) in enumerate(valid_loader):
            outputs = model(images)
            loss = loss_fn(outputs, labels)
            
            valid_losses.append(loss.item())
            
            _, predicted = torch.max(outputs.data, 1)
            correct += (predicted == labels).sum().item()
            total += labels.size(0)
            
    mean_train_losses.append(np.mean(train_losses))
    mean_valid_losses.append(np.mean(valid_losses))
    
    accuracy = 100*correct/total
    valid_acc_list.append(accuracy)
    print('epoch : {}, train loss : {:.4f}, valid loss : {:.4f}, valid acc : {:.2f}%'.format(epoch+1, np.mean(train_losses), np.mean(valid_losses), accuracy))





# Saving weights and models
print("Dumping weights and biases")
np.savetxt('l0_w.out', model.fc_layer0.weight.data.numpy(), fmt='%1.8f')
np.savetxt('l0_b.out', model.fc_layer0.bias.data.numpy(), fmt='%1.8f')
np.savetxt('l2_w.out', model.fc_layer2.weight.data.numpy(), fmt='%1.8f')
np.savetxt('l2_b.out', model.fc_layer2.bias.data.numpy(), fmt='%1.8f')

fig, (ax1, ax2) = plt.subplots(nrows=1, ncols=2, figsize=(15, 10))
ax1.plot(mean_train_losses, label='train')
ax1.plot(mean_valid_losses, label='valid')
lines, labels = ax1.get_legend_handles_labels()
ax1.legend(lines, labels, loc='best')

ax2.plot(valid_acc_list, label='valid acc')
ax2.legend()

plt.show()




'''
model.eval()
test_preds = torch.LongTensor()

for i, images in enumerate(test_loader):
    outputs = model(images)
    
    pred = outputs.max(1, keepdim=True)[1]
    test_preds = torch.cat((test_preds, pred), dim=0)





out_df = pd.DataFrame()
out_df['ID'] = np.arange(1, len(X_test.index)+1)
out_df['label'] = test_preds.numpy()

out_df.head()




out_df.to_csv('submission.csv', index=None)

'''