FROM node:16 as ministry_build

WORKDIR /usr/src/app
COPY package*.json ./
RUN npm install

FROM ministry_build
COPY . .
EXPOSE 3000
CMD ["node", "index.js"]
