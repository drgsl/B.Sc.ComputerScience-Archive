FROM node:14

#Creating app directory
WORKDIR /usr/src/app

#Installing app dependencies using both package.json and package-lock.json
COPY package*.json ./

RUN npm install

COPY . .

EXPOSE 3000

CMD [ "node", "app.js"]