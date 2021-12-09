module.exports = {
    async rewrites() {
      return [
        {
          source: '/api/:path*',
          destination: 'http://pictureFrame.local/:path*' // Proxy to Backend
        }
      ]
    }
  }